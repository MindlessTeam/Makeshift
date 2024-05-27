# MAKESHIFT

Makeshift is an adventure into the world of 3d-graphics (my 23rd adventure to be precise) with the goal to create a functional 3d game engine with an Editor. I want to bring the engine to a point where I can use it to produce a teenie tiny game.

## Architecture
*(Basic)*

![EngineArchitecture](https://user-images.githubusercontent.com/82168319/215982333-34038078-1cd6-4fab-abd8-b83dda50e119.png)

*(Game "Loop")*

![EngineLoop](https://user-images.githubusercontent.com/82168319/215982357-bc547e4a-6783-4998-bf80-e3145f6d569a.png)

## NOTE

Because Makeshift is a project intended for learning and I am in no way an expert (or *experienced*) with C++ and/or Computer Science, its code is most likely quite inefficient and doesn't sport the best design decisions. I do not recommend that this engine be used in any serious production, even when it's finished.

---

## Third-Party

Makeshift uses the following third-party libraries. Their respective licenses can be found in `licensing\`.
- premake *(build program)*
- GLFW *(window handling)*
- glm *(maths)*
- imgui *(editor and debug UI)*
- jsoncpp *(json loading and writing)*
- spdlog *(logging)*
- stb_image.h *(image-loading)*
- tiny_obj_loader.h *(obj-loading)*

## Special Thanks to:

- LearnOpenGL.com
- The Cherno
- Brackeys
- The Godot development team
- Valve Software

---

## LICENSING

Makeshift is licensed under the MIT-license, for more details see <a href="https://github.com/MindlessTeam/Makeshift/blob/main/.github/LICENSE.txt">LICENSE.txt</a>.
