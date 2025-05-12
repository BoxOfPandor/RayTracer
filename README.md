RayTracer

A C++ ray tracing engine that renders 3D scenes with various primitives, materials, and lighting effects.

## Overview

This ray tracer implements the fundamentals of ray tracing including:

- Camera and ray generation
- Primitive intersection (spheres)
- Lighting (directional lights)
- Materials with ambient, diffuse, and specular properties
- Shadow casting
- Scene configuration through config files

## Requirements

- C++ compiler with C++17 support
- libconfig++ (for scene configuration loading)

## Building
```bash
make
```

## Usage
```bash
./raytracer <SCENE_FILE>
```
Where `<SCENE_FILE>` is a scene configuration file using the libconfig format.
The renderer will produce a PPM file named `output.ppm` in the current directory.

Configuration File Format

The ray tracer uses the libconfig format for scene configuration. Below is a comprehensive guide to creating scene files.

### Basic Structure
A scene file consists of three main sections:
```
camera = { ... }    # Camera configuration
primitives = { ... } # Scene objects
lights = { ... }     # Light sources
```

### Camera Configuration
```
camera = {
  resolution = {
    width = 800;     # Image width in pixels
    height = 600;    # Image height in pixels
  };
  position = {
    x = 0.0;         # Camera position X
    y = 0.0;         # Camera position Y
    z = 0.0;         # Camera position Z
  };
  fieldOfView = 72.0; # Field of view in degrees
};
```

### Primitives
#### Spheres
```
primitives = {
  spheres = (
    {
      x = 0.0;       # Center X position
      y = 0.0;       # Center Y position
      z = -5.0;      # Center Z position
      r = 1.0;       # Radius
      color = {
        r = 255;     # Red component (0-255)
        g = 0;       # Green component (0-255)
        b = 0;       # Blue component (0-255)
      };
    },
    {
      x = 2.0;
      y = 1.0;
      z = -5.0;
      r = 0.5;
      color = {
        r = 0;
        g = 255;
        b = 0;
      };
    }
  );
};
```

### Lights
#### Directional Lights
Directional lights are defined by a direction vector, color, and intensity:
```
lights = {
  ambient = 0.1;     # Global ambient light level
  diffuse = 0.7;     # Global diffuse light level

  directional = (
    {
      x = 1.0;       # Direction vector X
      y = -1.0;      # Direction vector Y
      z = -1.0;      # Direction vector Z
      color = {
        r = 255;     # Red component (0-255)
        g = 255;     # Green component (0-255)
        b = 255;     # Blue component (0-255)
      };
      intensity = 1.0; # Light intensity
    }
  );
};
```

### Complete Example
Here's a complete example of a scene config file with one sphere and one directional light:
```
camera = {
  resolution = {
    width = 1280;
    height = 720;
  };
  position = {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  };
  fieldOfView = 72.0;
};

primitives = {
  spheres = (
    {
      x = 0.0;
      y = 0.0;
      z = -5.0;
      r = 1.0;
      color = {
        r = 255;
        g = 0;
        b = 0;
      };
    },
    {
      x = -2.0;
      y = 0.0;
      z = -6.0;
      r = 1.5;
      color = {
        r = 0;
        g = 0;
        b = 255;
      };
    }
  );
};

lights = {
  ambient = 0.1;
  diffuse = 0.7;

  directional = (
    {
      x = 1.0;
      y = -0.5;
      z = -1.0;
      color = {
        r = 255;
        g = 255;
        b = 255;
      };
      intensity = 0.8;
    },
    {
      x = -1.0;
      y = -0.5;
      z = -1.0;
      color = {
        r = 255;
        g = 220;
        b = 180;
      };
      intensity = 0.6;
    }
  );
};
```

This configuration will render a scene with two spheres (red and blue) lit by two directional lights.

## Advanced Configuration
### Material Properties
The material properties for all primitives can be adjusted by modifying the FlatMaterial parameters:
- `ambient`: The ambient reflection coefficient (default: 0.1)
- `diffuse`: The diffuse reflection coefficient (default: 0.7)
- `specular`: The specular reflection coefficient (default: 0.2)
- `shininess`: Controls the size of specular highlights (default: 50)

In the current implementation, these are defined at the code level but can be extended to be configurable in the scene file.

## Notes
- The ray tracer uses a right-handed coordinate system
- The camera looks toward the negative Z axis by default
- The PPM output format is a simple uncompressed image format that can be converted to other formats using tools like ImageMagick
