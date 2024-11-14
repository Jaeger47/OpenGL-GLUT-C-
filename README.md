
# OpenGL Projects Collection

This repository is a collection of OpenGL projects designed to demonstrate various graphics programming concepts, ranging from foundational 2D primitives to complex 3D transformations, lighting, texturing, and shader effects. Each project focuses on a specific OpenGL technique or feature, making this a comprehensive resource for anyone looking to learn or explore the power of OpenGL in rendering visual effects.

## Table of Contents

- [Overview](#overview)
- [Projects](#projects)
- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)
- [Acknowledgements](#acknowledgements)

---

## Overview

The projects in this collection span a wide range of topics:

- **Fundamentals**: Start with the basics of window creation, drawing simple shapes, and applying colors.
- **3D Rendering**: Dive into 3D transformations, depth, and perspective, creating immersive scenes.
- **Lighting and Materials**: Understand how light interacts with materials to create realistic visual effects, including ambient, diffuse, and specular lighting.
- **Textures**: Learn how to apply static, animated, and multi-textures to 3D objects, including texture wrapping and blending for advanced surface effects.
- **Interactivity**: Implement event-driven interactions using keyboard and mouse input for a dynamic user experience.
- **Advanced Effects**: Experiment with fog, blending, shaders, and first-person camera movement to add complexity to scenes.
- **Audio Integration**: Explore basic audio playback synchronized with OpenGL scenes for multimedia applications.

Each project contains a standalone example with its own source code and instructions, making it easy to explore specific features individually or incorporate them into larger projects.

---

## Projects

Here is a brief summary of each project included in this collection:

1. **A. Hello Window** - Initializes a basic OpenGL window using GLUT with a simple color buffer clear operation.
2. **B. Primitives** - Demonstrates drawing fundamental geometric shapes like triangles and squares.
3. **C. Transformations** - Introduces transformations such as translation, rotation, and scaling applied to 2D objects.
4. **D. Colors** - Applies color attributes to various primitives, demonstrating gradients and vertex colors.
5. **E. Going3D** - Sets up 3D rendering with depth buffering and basic perspective transformations.
6. **F. Lighting & Material** - Sets up ambient and specular lighting alongside material properties for realistic shading.
7. **F-2. Simple Lighting & Material** - A simplified approach to lighting, focusing on ambient and diffuse properties.
8. **F-3. Lighting Transformation** - Adds transformations to light sources, illustrating dynamic lighting effects.
9. **G. Textures** - Demonstrates loading and applying textures to 3D objects using `stb_image`.
10. **G-2. Texture Wrapping** - Shows different texture wrapping techniques like repeat, mirror, and clamp.
11. **G-3. Animated Textures** - Creates an animated effect by switching textures sequentially on a surface.
12. **H. Quadric & MultiTexture** - Uses quadric objects with multiple textures to add surface complexity.
13. **I. GlutModelTexture** - Loads textures on 3D models created with GLUT, adding realism to objects.
14. **J. Blending** - Explores blending modes to create transparency and overlay effects.
15. **K. Fog** - Adds atmospheric fog effects, creating a sense of depth.
16. **L. Event Callback** - Implements interactive controls and collision detection using keyboard events.
17. **M. Text** - Renders text using GLUT's bitmap fonts, useful for information display.
18. **N. Sound** - Integrates sound playback with the BASS library, synchronized with visual elements.
19. **O. Camera** - Implements a basic camera system allowing for scene exploration.
20. **Z. Extra Tutorials**
    - **FPS Camera**: First-person navigation of a 3D scene.
    - **Full Animated Textures**: Full-screen texture animations for advanced effects.
    - **Full Model Animation with Textures**: Frame-by-frame model animation.
    - **OpenGL Shaders**: Basic shader programming with GLSL.
    - **Scene Transition**: Simple transitions between multiple scenes.

---

## Getting Started

### Prerequisites

To run these projects, you’ll need:
- **OpenGL**: A compatible version of OpenGL with GLUT.
- **[Code::Blocks Portable](https://codeblocks.codecutter.org/) IDE**: A C++ IDE to compile and run these projects.
- **BASS Audio Library**: For projects involving sound (optional if audio isn’t required).
- **stb_image**: The `stb_image.h` file is included for loading images as textures.

### Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/OpenGL-Projects-Collection.git
   ```

2. Open Code::Blocks, navigate to **File > Open**, and select the `.cbp` project file in the project directory you want to explore.

3. Ensure that all required libraries (like BASS and OpenGL) are configured in Code::Blocks.

---

## Usage

Each project has a `main.cpp` file as the entry point. Follow these steps to compile and run a project in Code::Blocks:

1. **Open the Project**:
   - Open Code::Blocks and load the `.cbp` file for the specific project (e.g., `Hello Window.cbp`).

2. **Compile the Project**:
   - Use the **Build** option in Code::Blocks to compile the project.

3. **Run the Executable**:
   - After compilation, click **Run** to execute the project and see the OpenGL visualization.

### Example Execution

- Open Code::Blocks and load the `.cbp` file of your chosen project.
- Build and run the project to see the example in action.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- **GLUT**: Utility toolkit used for window management and input handling.
- **stb_image**: Library by Sean Barrett, used for loading images as textures.
- **BASS Audio Library**: Used for integrating audio playback in OpenGL scenes.
- Special thanks to OpenGL tutorials and resources that inspired and supported the creation of these examples.
