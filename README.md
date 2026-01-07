# wifiControlledMotor
This is a starter code to use wifi to control  esp motors

### Installation 
for esp idf,follow through https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html

## 🧪 Step 2 — Activate Conda Environment

Activate the ESP-IDF Python environment:

```bash
conda activate esp-idf-py38
```

> ⚠️ If you don’t have this environment yet, create it using:
```bash
conda create -n esp-idf-py38 python=3.8
conda activate esp-idf-py38
```

---

## 🔧 Step 3 — Setup ESP-IDF Toolchain Path

Export the Xtensa toolchain path:

```bash
export PATH=$HOME/.espressif/tools/xtensa-esp32s3-elf/esp-2021r2-patch5-8.4.0/xtensa-esp32s3-elf/bin:$PATH
```

> ✅ Tip: You may want to add this line to your `~/.bashrc` to avoid repeating it every time.

---

## 🗂️ Step 4 — Navigate to ESP-IDF Directory

```bash
cd ~/Project/esp32Setup/esp-idf || exit 1
```

---

## 🌱 Step 5 — Load ESP-IDF Environment

Source the ESP-IDF environment script:

```bash
source export.sh
```

You should now see ESP-IDF tools available:
```bash
idf.py --version
```

---



# To Build this project and flash it to esp32 s3
1. connect your esp32s3 to your computer
2. find the port your esp32s3 is connected to using <find the command>
3. ```bash
   git clone https://github.com/Arpan12/wifiControlledMotor.git
   cd wifiControlledMotor
   idf.py set-target esp32s3 ##(need to be done only once)
   idf.py build
   idf.py flash -p /dev/ttyACM0 <Replace this with your port>
   idf.py monitor
   ```
6. 
