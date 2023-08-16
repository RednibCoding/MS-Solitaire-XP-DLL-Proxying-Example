# MS Solitaire XP DLL Proxying Example

This project demonstrates how to write a proxy DLL to hijack a game/application via DLL proxying.
Specifically, this project targets the old game, MS Solitaire XP, and proxies the original cards.dll.

## How the Proxy Works

The proxy works by redirecting calls from the Solitaire game that are intended for the cards.dll to our proxy DLL (cards.dll).
Once the calls are intercepted by our proxy, we can execute any additional code (for instance, any "weaponized" code), and then forward these calls to the original cards.dll (which we've renamed to cards_og.dll).

## Function Forwarding with `cards.def`

In our project, not all functions from the original `cards.dll` are intercepted for modifications. Many of them are simply forwarded to the original DLL without any intervention on our part.

The `cards.def` file describes these functions. When the Solitaire game makes a call to any of these functions, our proxy DLL will transparently forward the call to the original `cards.dll` (renamed to `cards_og.dll`). This ensures that only specific functions (those we choose) are intercepted and modified, while the rest maintain their original behavior.

Here's a snippet from the `cards.def` file:

```
EXPORTS
cdtAnimate=cards_og.dll.cdtAnimate @2
cdtDraw=cards_og.dll.cdtDraw @3
cdtDrawExt=cards_og.dll.cdtDrawExt @4
cdtTerm=cards_og.dll.cdtTerm @6
```

For functions where we intend to introduce our own behavior or code, we need to provide their definitions in the `cards_proxy.cpp` file. This allows us to modify, intercept, or enhance their behavior as needed.

## Dive Deeper with Code Comments

For those interested in a more in-depth understanding of the DLL proxying mechanism, refer directly to the `cards_proxy.cpp` file. I've included detailed comments for each significant code segment, ensuring that you grasp the nuances of each operation. Whether you're a beginner or an expert, the code annotations will guide you through the intricacies of DLL proxying in this project.

## Building the Project with MSYS2

1. Compile the DLL Proxy:

   - Build the project by running the `build.sh` script:
     ```bash
     sh build.sh
     ```
     This script generates the proxy `cards.dll`. For a detailed explanation of how the `build.sh` script works, please refer to the comments inside the `build.sh` script itself.

2. Setup Game Directory:

   - Navigate to the MS Solitaire XP game directory.
   - Rename the original `cards.dll` to `cards_og.dll`.
   - Copy the generated `cards.dll` (produced from this project) to the game directory.

3. Run MS Solitaire XP:
   - Launch the game. It will now use the proxy DLL, which intercepts and can modify the behavior of certain functions.

# Setting up MSYS2 on Windows (only for Windows users that don't have MSYS2 installed)

To compile the project on Windows, we recommend using MSYS2. Here's how to set it up:

1. Install MSYS2: Download and install MSYS2 from their official website: https://www.msys2.org/.
2. Launch MSYS2: Start the MSYS2 application.
3. Install GCC: In the terminal window that appears, execute the following command to install the GCC compiler:

```bash
pacman -S mingw-w64-x86_64-gcc
```

4. Install Additional Tools: Execute the following command to install necessary tools and libraries:

```bash
pacman -S --needed base-devel mingw-w64-i686-toolchain
```

> When prompted, press Enter to install all suggested packages.

## Disclaimer

Using this project to alter the behavior of software, especially without permission, can be against the terms of service or even illegal in some contexts. Always ensure you have appropriate permissions and exercise ethical considerations when modifying or intercepting software behavior. This project is for educational purposes only.
