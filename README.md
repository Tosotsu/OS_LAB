# OS_LAB — Operating Systems Lab Experiments

Collection of C programs and documentation covering core OS concepts, written as lab assignments. Covers scheduling, memory management, page replacement, and disk scheduling algorithms.

## What It Does

Implements and compares classic OS algorithms from scratch in C:

| Experiment | Topic |
|------------|-------|
| exp2 | CPU Scheduling (FCFS, SJF, Round Robin, Priority) |
| exp3 | Process Synchronization |
| exp4 | Deadlock Detection & Avoidance |
| exp5 | Inter-Process Communication |
| exp6 | Memory Management (contiguous allocation) |
| exp7 | Virtual Memory |
| exp8 | Memory Management (paging, segmentation) |
| exp9 | Page Replacement (FIFO, LRU, Optimal) |
| exp10 | Disk Scheduling (FCFS, SSTF, SCAN, C-SCAN) |

## Tech Stack

- **Language:** C
- **Companion docs:** Markdown explanations for each experiment

## Practical Use

Reference implementations for OS course lab work — each experiment includes working C code plus a markdown explanation of the algorithm's logic, trade-offs, and sample output. Useful for exam prep and understanding how real OS kernels manage resources.

## Run Any Experiment

```bash
gcc exp2/program.c -o out && ./out
```

Each experiment folder is self-contained. See the corresponding `_explanation.md` and `scheduling_comparison.md` for context.
