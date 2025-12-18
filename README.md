Trace is a geolocater written in C designed for the linux terminal

# Installation
- Clone the repo: ```git clone https://github.com/MisterArchMan/trace.git```
- Compile the C file: ```gcc main.c -o main -lcurl```
- Run: ```./main```

- If you want, you can move the executable to /usr/local/bin to run the executable from anywhere

# Dependencies for Debian/Ubuntu/Fedora
- Fedora: sudo dnf install libcurl-devel
- Debian/Ubuntu: sudo apt install libcurl4-openssl-dev
