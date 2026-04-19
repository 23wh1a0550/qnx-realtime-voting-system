#include <stdio.h>          // For input/output functions
#include <sys/neutrino.h>   // QNX message passing functions

// -------- MESSAGE STRUCT (Admin → Server) --------
typedef struct {
    int type;       // Request type (3 = admin request)
    int voter_id;   // Not used in admin
    int biometric;  // Not used in admin
    int candidate;  // Not used in admin
} Msg;

// -------- REPLY STRUCT (Server → Admin) --------
typedef struct {
    int status;          // 1=success, 0=failure
    char message[100];   // Response message
    int votes[3];        // Vote count for each candidate
} Reply;

int main() {

    // Connect to the server using its registered name
    int coid = name_open("voting_server", 0);

    Msg msg;        // Message to send
    Reply reply;    // Reply from server

    // Set request type as ADMIN
    msg.type = 3;   // Type 3 indicates admin access

    // Send request to server and receive vote data
    MsgSend(coid, &msg, sizeof(msg), &reply, sizeof(reply));

    // Display heading
    printf("\n--- ADMIN LIVE RESULTS ---\n");

    // Print vote count for each candidate
    for (int i = 0; i < 3; i++) {
        printf("Candidate %d: %d votes\n", i, reply.votes[i]);
    }

    // Close connection with server
    name_close(coid);

    return 0;
}
