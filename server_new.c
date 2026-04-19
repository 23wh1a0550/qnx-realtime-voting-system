#include <stdio.h>          // Standard I/O functions
#include <stdlib.h>         // General utilities
#include <string.h>         // String handling
#include <sys/neutrino.h>   // QNX message passing
#include <sys/dispatch.h>   // name_attach()
#include <pthread.h>        // Threading & mutex

#define MAX_USERS 5         // Maximum voters allowed

// -------- STRUCT --------

// Voter database structure
typedef struct {
    int voter_id;       // Unique voter ID
    int biometric;      // Biometric (PIN/fingerprint simulation)
    int has_voted;      // Flag to check if already voted
    int vote_attempts;  // Count of vote attempts (for anomaly detection)
} Voter;

// Message sent from client to server
typedef struct {
    int type;       // 1=authentication, 2=voting, 3=admin request
    int voter_id;
    int biometric;
    int candidate;
} Msg;

// Reply sent from server to client
typedef struct {
    int status;          // 1=success, 0=failure
    char message[100];   // Message for client
    int votes[3];        // Vote count for each candidate
} Reply;


// -------- DATABASE --------

// Predefined voters (ID, biometric, has_voted, attempts)
Voter voters[MAX_USERS] = {
    {101,201,0,0},
    {102,202,0,0},
    {103,203,0,0},
    {104,204,0,0},
    {105,205,0,0}
};

// Vote count for 3 candidates
int votes[3] = {0};

// Mutex for thread safety (avoid race conditions)
pthread_mutex_t lock;


// -------- FIND USER FUNCTION --------

// Function to find voter in database
int find_user(int voter_id, int biometric) {
    for (int i = 0; i < MAX_USERS; i++) {
        // Match both voter ID and biometric
        if (voters[i].voter_id == voter_id && voters[i].biometric == biometric)
            return i;   // Return index if found
    }
    return -1;          // Not found
}


// -------- MAIN FUNCTION --------

int main() {

    name_attach_t *attach;

    // Create a communication channel (server name)
    attach = name_attach(NULL, "voting_server", 0);
    if (attach == NULL) {
        perror("name_attach failed");
        return -1;
    }

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    printf("🔥 QNX Secure Voting Server Started...\n");

    // Infinite loop to handle multiple clients
    while (1) {

        Msg msg;                 // Incoming message
        Reply reply = {0};       // Initialize reply (important to avoid garbage values)
        int rcvid;

        // Receive message from client
        rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);
        if (rcvid == -1)
            continue;

        // -------- LOGGING --------
        printf("\n📩 Client Connected\n");
        printf("Received -> Type:%d VoterID:%d Biometric:%d Candidate:%d\n",
               msg.type, msg.voter_id, msg.biometric, msg.candidate);

        // Lock critical section (shared data protection)
        pthread_mutex_lock(&lock);

        // Find voter in database
        int index = find_user(msg.voter_id, msg.biometric);

        // -------- AUTHENTICATION FAILURE --------
        if (index == -1) {
            reply.status = 0;
            strcpy(reply.message, "Voter ID or Biometric mismatch!");
        }

        // -------- AUTHENTICATION --------
        else if (msg.type == 1) {

            // Check if voter already voted
            if (voters[index].has_voted) {
                reply.status = 0;
                strcpy(reply.message, "You have already voted!");
            }
            else {
                reply.status = 1;
                strcpy(reply.message, "Access Granted. Enter Voting Room.");
            }
        }

        // -------- VOTING --------
        else if (msg.type == 2) {

            // Increment attempt count
            voters[index].vote_attempts++;

            // Detect suspicious activity
            if (voters[index].vote_attempts > 3) {
                printf("\n🚨 ALERT: Abnormal activity detected for Voter ID %d\n",
                       msg.voter_id);
            }

            // If already voted
            if (voters[index].has_voted) {
                reply.status = 0;
                strcpy(reply.message, "Already voted!");
            }

            // Invalid candidate input
            else if (msg.candidate < 0 || msg.candidate > 2) {
                reply.status = 0;
                strcpy(reply.message, "Invalid candidate!");
            }

            // Valid vote casting
            else {
                voters[index].has_voted = 1;     // Mark as voted
                voters[index].vote_attempts = 0; // Reset attempts

                votes[msg.candidate]++;          // Increment vote count

                reply.status = 1;
                strcpy(reply.message, "Vote Casted Successfully!");
            }
        }

        // -------- ADMIN REQUEST --------
        else if (msg.type == 3) {
            reply.status = 1;
            strcpy(reply.message, "Admin Access");
        }

        // Copy vote results to reply
        for (int i = 0; i < 3; i++) {
            reply.votes[i] = votes[i];
        }

        // Unlock critical section
        pthread_mutex_unlock(&lock);

        // Send reply back to client
        MsgReply(rcvid, 0, &reply, sizeof(reply));
    }

    return 0;
}
