# RoughCopy

    RoughCopy is a lightweight C++/Qt6 powered **code editor** 
    designed with simplicity and speed in mind.  
    It provides a distraction-free editing experience 
    with theme support, customizable fonts, and a clean UI.

---

## ✨ Features
- 🚀 Built with **C++17** and **Qt6** for native performance.
- 🎨 **Themes**:
  - Light
  - Dark
  - Night Sky
- 🔤 **Font customization** (family + size).
- 🎛️ **Preferences dialog** with live preview.
- 🖌️ Configurable font and background colors.
- ⌨️ Syntax-friendly editor with smooth caret.
- 🧩 Extendable architecture (planned: minimap, syntax highlighting).

---

## 📦 Installation

    1. From `.deb` package
        [bash]
            $ sudo dpkg -i roughcopy_1.0-1_amd64.deb
            $ sudo apt-get -f install   # to fix missing dependencies if any

    2. From source :
        [bash]
            $ git clone https://github.com/SouradipPatra7904/RoughCopy.git
            $ cd RoughCopy
            $ mkdir build && cd build
            $ cmake ..
            $ make -j$(nproc)
            $ ./RoughCopy
