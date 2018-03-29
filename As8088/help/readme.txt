#What to do if "file not found" for *88 executables:

https://askubuntu.com/questions/133389/no-such-file-or-directory-but-the-file-exists

I.

You're probably trying to run a 32-bit binary on a 64-bit system that doesn't have 32-bit support installed.

There are three cases where you can get the message “No such file or directory”:

The file doesn't exist. I presume you've checked that the file does exist (perhaps because the shell completes it).
There is a file by that name, but it's a dangling symbolic link.
The file exists, and you can even read it (for example, the command file shank-linux-120720110-1-bin displays something like “ELF 32-bit LSB executable …”), and yet when you try to execute it you're told that the file doesn't exist.
The error message in this last case is admittedly confusing. What it's telling you is that a key component of the runtime environment necessary to run the program is missing. Unfortunately, the channel through which the error is reported only has room for the error code and not for this extra information that it's really the runtime environment that's to blame. If you want the technical version of this explanation, read Getting “Not found” message when running a 32-bit binary on a 64-bit system.

The file command will tell you just what this binary is. With a few exceptions, you can only run a binary for the processor architecture that your release of Ubuntu is for. The main exception is that you can run 32-bit (x86, a.k.a. IA32) binaries on 64-bit (amd64, a.k.a. x86_64) systems.

In Ubuntu up to 11.04, to run a 32-bit binary on a 64-bit installation, you need to install the ia32-libs package Install ia32-libs. You may need to install additional libraries (you'll get an explicit error message if you do).

Since 11.10 (oneiric) introduced multiarch support, you can still install ia32-libs, but you can choose a finer-grained approach, it's enough to get libc6-i386 Install libc6-i386 (plus any other necessary library).

II.

Follow this answer only if the output of file file-name shows,

file-name: ELF 32-bit LSB  executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.8, not stripped
To run 32bit executable file in a 64 bit multi-arch Ubuntu system, you have to add i386 architecture and also you have to install libc6:i386,libncurses5:i386,libstdc++6:i386 these three library packages.

sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386
./file-name