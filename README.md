**Computer Graphics Final Project: Kenya Flag & TikTok Logo Implementation

**Group Members:**
- Birhanu Fiseha (GUR/02498/15)
- Bihoney Gebremeskel (GUR/01020/16)
- Atinaw Dessie (GUR/22848/16)
- Temesegen Dessie (GUR/01339/16)
- Hayat Seid (GUR/02851/16)
- Solomon Setegn (GUR/01568/16)

# Kenya Flag Rendering Project – Explanation Document

## 1. Transformations Used

### a) Translation (`glTranslatef`)
- **Purpose:** Used to position discrete elements relative to the shield's center.
- **Application:** 
  - Positions the black "ears" on either side of the main shield body.
  - Moves the white teardrop patterns vertically above and below the center.
- **Implementation:** Achieved by pushing the matrix state (`glPushMatrix`), applying the translation, drawing the object, and restoring the state (`glPopMatrix`).

### b) Rotation (`glRotatef`)
- **Purpose:** To orient the spears dynamically.
- **Application:** Applied to both spears to angle them at ±42° relative to the vertical axis.
- **Result:** Creates a realistic crossing effect behind the shield, adding depth to the composition.

### c) Scaling (Bonus: Implicit via Wave Animation)
- **Concept:** While no explicit `glScalef` was used, the waving effect dynamically alters the apparent dimensions of the objects.
- **Mechanism:** The sine wave function displaces vertices along the Y-axis based on their X-position, effectively stretching and compressing the visual geometry parametrically.
- **Significance:** Demonstrates an understanding of **parametric deformation** rather than static scaling.

## 2. Implementation Details
- **Primitives Used:**
  - `GL_QUADS`: Flag stripes and pole body
  - `GL_POLYGON`: Shield shapes, golden ball, curved elements
  - `GL_LINES`: Decorative rings and diagonal patterns on flagpole
  - `GL_POINTS`: Rivets/studs decoration along the flagpole
- **High-Resolution Primitives:** All curved shapes are constructed using `GL_POLYGON` with high-resolution sampling (100 steps per curve segment) to ensure smooth edges without jagged artifacts.
- **Superellipse Geometry:** The iconic Maasai shield shape is generated mathematically using the superellipse formula:
  $$width = maxWidth \times (1 - |t|^P)^{(1/P)}$$
  This allows for precise control over the curvature ("sharpness") of the shield.
- **Color Accuracy:**Colors are hardcoded using RGB values matching the official Kenyan flag specifications: Red (#BC0000 → 0.737f, 0.0f, 0.0f), Green (#006600 → 0.0f, 0.4f, 0.0f), Black (0.0f, 0.0f, 0.0f), and White (1.0f, 1.0f, 1.0f).
- **Animation Loop:** The `waveOffset` (time) variable is updated every frame, driving the sinusoidal displacement calculation for all vertices.

## 3. Challenges Faced

- **Element Alignment:** Aligning the black "ears" perfectly with the red shield curve required precise mathematical matching of the superellipse parameters. Any mismatch resulted in visible gaps.
- **Layering Order:** Ensuring the central white circle appeared cleanly on top of the red divider required a specific drawing order (Divider first, Circle second) to handle depth correctly in 2D space.
- **Synchronized Animation:** The most significant challenge was animating the shield without it appearing to "float" separately from the flag. 
  - **Solution:** Solved by applying the **exact same wave offset function** to every vertex in the scene, regardless of whether it belonged to the background or the emblem.

## 4. Bonus Feature: Animated Waving Flag

- **Unified Vertex Transformation:** Implemented a single global function `drawVertexWaved(x, y)` that applies the formula $y_{new} = y + A \cdot \sin(k \cdot x + \omega t)$ to **every** vertex in the scene (both background stripes and shield emblem).
- **Coordinate Mapping:** This ensures perfect synchronization; if the flag fabric at $x=50$ moves up, the shield pixel at $x=50$ moves by the exact same amount, eliminating "floating" artifacts and gaps.
- **Horizontal Propagation:** The wave depends on the $x$-coordinate, creating realistic humps that travel from left (flagpole) to right.
- **Geometry Integrity:** The shape definitions (`drawMaasaiShapeRaw`) remain static and distortion-free; the wave is applied only at the final rendering stage, demonstrating advanced **Vertex Transformation** and **Coordinate Mapping**.
- **Smooth Rendering:** Achieved continuous animation using `glutPostRedisplay()` coupled with double buffering (`GLUT_DOUBLE`).

# TikTok Logo Implementation - OpenGL

## 1. Course Concepts Applied
* **Basic Primitives:** * `GL_QUADS`: Used for the vertical stem of the musical note.
    * `GL_QUAD_STRIP`: Used for the complex curved "belly" and "hook" (flag) of the note to ensure smooth color filling.
    * **Points/Lines:** Mathematical calculations using `sin()` and `cos()` to plot points along arcs.
* **Color Handling:** * Implemented official TikTok branding colors using `glColor4f`.
    * **Cyan:** `RGB(37, 244, 238)` -> `(0.145, 0.957, 0.933)`
    * **Magenta:** `RGB(254, 44, 85)` -> `(0.996, 0.173, 0.333)`
    * **Black:** Pure `(0.0, 0.0, 0.0)` for the primary shape.
* **Transformations:**
    1.  `glTranslatef`: Used to create the "glitch" effect by offsetting the Cyan and Magenta layers from the center.
    2.  `glScalef`: Implemented a dynamic scale for the pulsing animation.
    3.  `glRotatef`: Applied a slight tilt (-2.0 degrees) to match the dynamic aesthetic of the brand.

## 2. Implementation Methodology
The logo utilizes a Z-order layered approach to recreate the iconic "glitch" aesthetic: 
1.  Cyan Layer: Rendered first with a top-left diagonal translation.
2.  Magenta Layer: Rendered second with a bottom-right diagonal translation.
3.  Black Layer: Rendered last at the origin $(0,0)$. This acts as a geometric mask, "swallowing" the internal overlapping colors to leave only the vibrant edge-fringes visible.

To ensure structural integrity, We implemented a -0.18f mathematical overlap where the curves meet the stem, ensuring a seamless merge across all three color layers.

# 3. Challenges Faced

- **Geometry Integration:** Connecting arcs to a straight stem created white "cracks" due to floating-point rounding. I solved this by calculating a -0.18f overlap offset to bury the edges and ensure a solid fill
- **Layered Glitch Alignment:** Diagonal translations $(X, Y)$ caused horizontal edges to "slide" out of level. I resolved this using a Z-order masking strategy, where the final Black layer "swallows" inner color overlaps to secure clean vertical alignment.
- **Synchronized Scaling:** To prevent layers from drifting apart during the animation, I applied a global glScalef transformation before individual translations, keeping the glitch effect perfectly proportional to the logo size.

## 4.Bonus Challenge: Pulsing Animation
I implemented a dynamic "Heartbeat" pulse to reflect the brand's musical identity:

**Logic:** Using glutIdleFunc, the program incrementally modifies a scaleFactor variable.

**Result:** The logo oscillates smoothly between 95% and 105% scale, simulating a bass-driven pulse that adds a professional, interactive dimension to the project.

## Conclusion

This project successfully demonstrates a comprehensive application of Computer Graphics principles covered in Chapters 3, 4, and 5:
-**Geometric Primitives:** Advanced use of GL_POLYGON and GL_QUAD_STRIP combined with parametric equations ($\sin$/$\cos$) to create Maasai shields and musical notes.
-**Color Science:** Implementation of precise brand/national identities using normalized RGB values.
-**Matrix Transformations:** Mastery of glTranslatef, glRotatef, and glScalef to manage complex scene hierarchies and object placement.
-**Advanced Creative Features:** Going beyond static rendering by implementing Vertex Deformation (Sine-wave flag animation) and Dynamic Scaling (Pulsing logo), showcasing an understanding of the OpenGL idle loop and time-based rendering.

## Setup and Running Instructions
1. Prerequisites
Ensure you have an OpenGL development environment set up. You will need:

A C++ compiler (e.g., MinGW for Windows or GCC for Linux).

GLUT or FreeGLUT libraries installed.

2. How to Compile
Open your terminal or command prompt and navigate to the project directory. Use the following command to compile:

Bash
g++ main.cpp -o GraphicsProject -lGL -lGLU -lglut
(Note: If you are on Windows, you may need to use -lfreeglut or -lopengl32 -lglu32 depending on your setup.)

3. How to Run
After successful compilation, run the executable:

For Windows:

Bash
GraphicsProject.exe
For Linux/macOS:

Bash
./GraphicsProject
4. Application Controls
Display: The program will open a single window.

Toggle View: Press the BACKSPACE key to switch between the Kenya Flag and the TikTok Logo.

Animation: Both scenes feature automatic animations (Waving effect for the flag and Pulsing effect for the logo).
