# 🖥️ Operating System Experiments and Concepts

This repository contains a collection of experiments, algorithms, and implementations of key operating system concepts, including process scheduling, memory allocation, disk scheduling, threads, synchronization mechanisms, and more. Each directory represents a different component or solution to specific operating system problems.

## 📋 Table of Contents
- [Introduction](#introduction)
- [Repository Structure](#repository-structure)
  - [Process Scheduling Algorithms](#process-scheduling-algorithms)
  - [Disk Scheduling Algorithms](#disk-scheduling-algorithms)
  - [Memory Allocation](#memory-allocation)
  - [Threading and Synchronization](#threading-and-synchronization)
  - [Banker's Algorithm](#bankers-algorithm)
  - [Page Replacement Algorithms](#page-replacement-algorithms)
- [Key Concepts](#key-concepts)
  - [Race Condition](#race-condition)
  - [Semaphore](#semaphore)
  - [Deadlock](#deadlock)
  - [Memory Management](#memory-management) 
- [Installation & Usage](#installation--usage)
- [Contributing](#contributing)

## 🚀 Introduction

This repository serves as a comprehensive resource for understanding and implementing fundamental operating system concepts. It includes practical implementations of various algorithms and solutions to classic operating system problems, making it valuable for both learning and reference purposes.

## 📁 Repository Structure

### Process Scheduling Algorithms

The `Scheduling Algos` directory contains implementations of various process scheduling algorithms:

- **First-Come-First-Serve (FCFS)** ⏱️: Processes are executed in the order they arrive
- **Shortest Job First (SJF)** 📉: Non-preemptive scheduling based on burst time
- **Round Robin (RR)** 🔄: Time-sliced scheduling with a fixed quantum
- **Priority Scheduling** ⭐: Execution order based on priority values
- **Shortest Remaining Time First (SRTF)** ⌛: Preemptive version of SJF
- **Gantt Chart Visualization** 📊: Added visualizations for scheduling algorithms

### Disk Scheduling Algorithms

The `Disk Scheduling Algo` directory implements common disk scheduling algorithms:

- **FCFS**: First-Come-First-Serve disk access
- **SCAN/Elevator**: Bi-directional disk arm movement
- **C-SCAN**: Circular SCAN algorithm
- **LOOK/C-LOOK**: Optimized versions of SCAN/C-SCAN

### Memory Allocation

The `Memory Allocation` directory contains implementations of memory allocation strategies:

- **First Fit**: Allocates the first available block that fits
- **Best Fit**: Allocates the smallest block that satisfies the request
- **Worst Fit**: Allocates the largest available block
- **Next Fit**: Modified first-fit starting from last allocation position

### Threading and Synchronization

The `Threads` directory focuses on thread management and synchronization:

- **Thread Creation**: Basic thread implementation
- **Mutex Implementation**: Mutual exclusion mechanisms
- **Semaphores**: Implementation of binary and counting semaphores
- **Producer-Consumer Problem**: Classic synchronization problem solution

### Banker's Algorithm

The `Banker's Algo` directory implements the Banker's algorithm for deadlock avoidance:

- **Resource Allocation Graph**: Visualization of system state
- **Safety Algorithm**: Determines if system is in safe state
- **Resource Request Algorithm**: Handles resource requests safely

### Page Replacement Algorithms

The `Replacement Algo` directory contains page replacement policies:

- **FIFO**: First-In-First-Out replacement
- **LRU**: Least Recently Used strategy
- **Optimal**: Theoretical optimal replacement policy
- **Clock/Second Chance**: Efficient approximation of LRU

## 🔑 Key Concepts

### Race Condition

🏁 Race conditions occur when multiple threads access shared data simultaneously, causing unpredictable behavior. This repository demonstrates both how race conditions manifest and how to prevent them through proper synchronization.

### Semaphore

🚦 Semaphores control access to shared resources through atomic operations. This repository implements:

- **Binary Semaphores**: Used for mutual exclusion (similar to locks)
- **Counting Semaphores**: Used for resource management with multiple units

### Deadlock

🔄 Deadlock situations arise when processes hold resources while waiting for others, creating a circular wait. This repository includes:

- **Deadlock Detection**: Algorithms to identify deadlock conditions
- **Deadlock Prevention**: Strategies to avoid deadlock situations
- **Banker's Algorithm**: Implementation of deadlock avoidance technique

### Memory Management

💾 Memory management techniques optimize the allocation and utilization of system memory:

- **Paging**: Fixed-size memory block management
- **Segmentation**: Variable-sized logical memory blocks
- **Virtual Memory**: Extended memory using disk storage
- **Page Replacement**: Algorithms for selecting pages to swap out

## 💻 Installation & Usage

```bash
# Clone the repository
git clone https://github.com/Faisal786111/os-experiments.git

# Navigate to the repository
cd os-experiments

# Explore different experiments
cd Experiments
```

## 🤝 Contributing

Contributions are welcome! If you have any improvements or new experiments to add:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-experiment`)
3. Commit your changes (`git commit -m 'Add some amazing experiment'`)
4. Push to the branch (`git push origin feature/amazing-experiment`)
5. Open a Pull Request
