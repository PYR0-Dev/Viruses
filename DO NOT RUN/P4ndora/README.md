# ☣️ P4ndora Virus (Educational / Research Only)

---

> ⚠️ **WARNING:** This repository contains **real, destructive malware source code**.  
> This program is designed to **render a Windows system unbootable** by overwriting the Master Boot Record (MBR) and corrupting system files.  
>  
> **Do NOT compile or execute this code on a physical machine.** > Use **strictly isolated virtual machines** (VMs) for analysis.

---

# 🔎 Overview

**P4ndora** is a destructive Trojan written in C++ that demonstrates how malware interacts with low-level Windows APIs. 

It is inspired by "joke" programs like MEMZ but carries a much more aggressive payload. It is intended for **educational study** of:

- **GDI Graphics Manipulation:** Direct drawing and color inversion on the desktop.
- **Low-Level Disk Access:** Overwriting the PhysicalDrive0 MBR.
- **System Sabotage:** Terminating critical processes like `winlogon.exe`.
- **Registry Persistence:** Using the Windows `Run` key for auto-execution.

---

# 🧪 Technical Details

- **Language:** C++
- **APIs Used:** Windows API (User32, GDI32, Advapi32)
- **Target OS:** Windows (7, 10, 11)

### Features:
- **Two-Stage Confirmation:** Prevents accidental execution with multi-step warnings.
- **Stealth:** Hides the console window immediately upon confirmation.
- **Visual Payloads:** Multi-threaded effects including screen inversion, mouse teleportation, and random error popups.
- **MBR Overwrite:** Replaces the boot sector with random data, destroying the OS boot path.

---

# ⚡ Stages of Execution

1. **Warning Phase:** Two Message Boxes prompt the user for consent.
2. **Persistence:** The binary copies itself to the system directory and adds a registry startup key.
3. **Annoyance Phase (30s):** Background threads trigger visual glitches and mouse interference.
4. **Destruction Phase:** - Critical system services are terminated (causing a BSOD).
    - Core system files are corrupted with garbage data.
    - The **MBR is overwritten**, preventing the PC from booting again.
    - A forced system restart is initiated.

---

# 🖥️ Safe Analysis

To study P4ndora without destroying your hardware:

1. **Read-Only Analysis:** Review the source code to understand API calls without compiling.
2. **Isolated VM:** Use a tool like **VirtualBox** or **VMware**.
3. **Snapshotting:** Always take a snapshot before running the executable.
4. **No Networking:** Ensure the VM "Network Adapter" is disconnected.

---

# ⚖️ Disclaimer

This project is provided **strictly for educational and research purposes**. 

The author **does not condone or encourage** the creation or distribution of malware. By accessing this code, you agree that:
- You are responsible for your own actions.
- You will only use this code in a **legal and ethical** manner.
- You understand the risks of handling destructive software.

**The author is not responsible for any damage caused by misuse of this code.**

---

# ⚠️ Final Warning

**Once the MBR is overwritten, the operating system is gone.** **Do not play with fire unless you are in a sandbox.**
