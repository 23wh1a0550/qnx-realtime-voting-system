# qnx-realtime-voting-system
Implementation of a real-time voting system leveraging QNX Neutrino RTOS microkernel architecture. The system demonstrates inter-process communication (IPC), multithreading, and deterministic scheduling, along with a lightweight AI module for real-time anomaly detection in voting patterns.
# Real-Time Secure Voting and Counting using QNX RTOS

## Team Details
**Team Name:** Syntax Squad  

- M. Vaishnavi (CSE)  
- G. Vishala (EEE)  
- B. Rohitha (ECE)  

**College:** BVRIT Hyderabad College of Engineering for Women  
Bachupally, Hyderabad, Telangana, India  

---

##  Project Overview
This project presents a **real-time secure voting and counting system** using **QNX RTOS**.  

Traditional voting systems suffer from:
- Delayed result generation  
- Lack of transparency  
- Risk of system failure and data loss  

To overcome these issues, our system provides:
- **Instant vote counting**
- **Secure data handling**
- **Continuous system operation**

---

## Problem Statement
- Traditional systems do not provide real-time results  
- System failures may cause data loss  
- Lack of transparency reduces trust  
- Handling multiple voters simultaneously is difficult  

---

##  Objective
- Implement real-time voting and counting  
- Ensure secure communication between terminals and server  
- Prevent duplicate and unauthorized voting  
- Maintain system reliability and fault tolerance  

---

## Proposed Solution
We developed a **client-server based voting system** where:

- Multiple voting terminals send votes  
- A central server processes and counts votes  
- QNX RTOS ensures real-time performance  
- AI module monitors suspicious activity  

---

##  System Architecture

###  Voting Terminals (Client)
- Accept user input (ID & PIN)  
- Display candidates  
- Send vote data to server  

###  Central Server
- Verifies user credentials  
- Stores votes securely  
- Counts votes in real time  
- Sends results to display module  

###  AI Monitoring Module
- Analyzes voting patterns  
- Detects suspicious activity  
- Prevents duplicate or abnormal voting  

---

##  Workflow
1. User enters ID and PIN  
2. Client sends data to server  
3. Server verifies user  
4. If valid, candidates are displayed  
5. User selects candidate  
6. Vote is sent to server  
7. AI module checks vote pattern  
8. If normal → vote stored  
9. If suspicious → alert generated  

---

##  Real-Time Features
- Instant vote counting  
- Multiple users voting simultaneously  
- Real-time result updates  
- Continuous system operation  
- Fast response using QNX scheduling  

---

##  AI Integration (Innovation)
We introduced an **AI-based anomaly detection module**:

###  What it does:
- Detects duplicate voting attempts  
- Identifies abnormal voting speed  
- Monitors repeated access from same user/device  

###  How it works:
- Collects data (user ID, time, device)  
- Applies rule-based detection  
- Flags suspicious activity in real time  

---

##  Security Features
- User authentication (ID & PIN)  
- Prevention of multiple voting  
- Secure communication using QNX IPC  
- Safe vote storage  
---

##  Technologies Used

### Hardware
- Raspberry Pi 4  
- Voting Terminals  

### Software 
- Embedded C / C++  

### Development Tools
- Windows
- QNX Momentics IDE  
---

##  QNX Implementation
- Uses **QNX  RTOS (Microkernel Architecture)**  
- Modules:
  - Authentication  
  - Voting  
  - Counting  
  - AI Monitoring  
  - Result Display  

- Communication via **QNX Message Passing (IPC)**  
- Ensures:
  - Real-time execution  
  - Fault tolerance  
  - Independent module operation  
---

##  Expected Results
- Secure and reliable voting system  
- Accurate vote counting  
- No data loss  
- Detection of suspicious voting behavior  
- High performance under multiple users  
---

##  Applications
- Government elections  
- University voting systems  
- Organizational decision-making  
- Digital polling platforms  
---

##  Future Enhancements
- Biometric / Face authentication  
- Blockchain-based vote storage  
- Mobile voting system  
---

##  Conclusion
This project provides a **secure, reliable, and real-time voting system** using QNX RTOS.  
The integration of **AI-based anomaly detection** enhances security and ensures election integrity.
---
