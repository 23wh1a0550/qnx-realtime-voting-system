#include <stdio.h>          // Standard input/output functions
#include <string.h>         // String handling
#include <sys/neutrino.h>   // QNX message passing functions

// -------- MESSAGE STRUCT (Client → Server) --------
typedef struct {
    int type;       // 1=authentication, 2=voting
    int voter_id;   // User ID
    int biometric;  // Biometric input (simulated)
    int candidate;  // Candidate choice
} Msg;

// -------- REPLY STRUCT (Server → Client) --------
typedef struct {
    int status;          // 1=success, 0=failure
    char message[100];   // Response message from server
    int votes[3];        // Vote count (used by admin, optional here)
} Reply;

int main() {

    // Connect to server using name
    int coid = name_open("voting_server", 0);
    if (coid == -1) {
        perror("name_open failed");  // Error if server not running
        return -1;
    }

    Msg msg;        // Message to send
    Reply reply;    // Reply from server

    // -------- AUTHENTICATION --------
    msg.type = 1;   // Type 1 = Authentication request

    // Take voter ID input
    printf("\nEnter Voter ID: ");
    fflush(stdout);                 // Force print immediately (fix alignment issue)
    scanf("%d", &msg.voter_id);

    // Take biometric input
    printf("Scan Biometric: ");
    fflush(stdout);                 // Ensure prompt appears before input
    scanf("%d", &msg.biometric);

    // Send authentication request to server
    MsgSend(coid, &msg, sizeof(msg), &reply, sizeof(reply));

    // Display server response
    printf("Server: %s\n", reply.message);

    // If authentication failed, exit program
    if (reply.status == 0) {
        name_close(coid);
        return 0;
    }

    // -------- VOTING --------
    printf("\n--- Candidates ---\n");
    printf("0 -> A\n1 -> B\n2 -> C\n");

    msg.type = 2;   // Type 2 = Voting request

    // Take candidate choice input
    printf("Enter your choice: ");
    fflush(stdout);
    scanf("%d", &msg.candidate);

    // Send vote to server
    MsgSend(coid, &msg, sizeof(msg), &reply, sizeof(reply));

    // Display voting result
    printf("Server: %s\n", reply.message);

    // Close connection with server
    name_close(coid);

    return 0;
}
