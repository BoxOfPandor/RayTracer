# RayTracer
A C++ ray tracing engine that renders 3D scenes with various primitives, materials, and lighting effects. This implementation supports multithreaded rendering with both PPM and SFML output options.

## Overview
This ray tracer implements key features of ray tracing including:
- Camera system with configurable field of view and positioning
- Multiple primitive types (spheres, cylinders)
- Materials with ambient, diffuse, and specular properties
- Directional lighting with color and intensity control
- Shadow casting and shading
- Builder pattern for scene construction
- Factory patterns for creating primitives, materials, and lights
- Scene configuration through libconfig files
- Real-time rendering preview with SFML

## Requirements
- C++ compiler with C++17 support
- libconfig++ (for scene configuration loading)
- SFML 2.6 (for real-time rendering preview)

## Building
```bash
make
```

## Usage
```bash
./raytracer [options] <scene_file>
```

### Command Line Options
- `--ppm <output.ppm>` - Render to PPM file (default)
- `--sfml <output.png>` - Render with SFML (real-time display + PNG output)
- `--threads <num>` - Number of rendering threads (SFML only, default: auto)
- `--help` - Display help message

Examples:
```bash
# Render with PPM
./raytracer --ppm output.ppm scenes/sample.cfg

# Render with SFML using 8 threads
./raytracer --sfml output.png --threads 8 scenes/sample.cfg
```

## Scene Configuration File Format
The ray tracer uses the libconfig format for scene configuration. Below is a comprehensive guide to creating scene files.

### Basic Structure
A scene file consists of three main sections:
```
camera = { ... }     # Camera configuration
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
      material = {
        ambient = 0.1;     # Ambient reflection coefficient
        diffuse = 0.7;     # Diffuse reflection coefficient
        specular = 0.2;    # Specular reflection coefficient
        shininess = 50.0;  # Controls the size of specular highlights
      };
    }
  );
};
```

#### Cylinders
```
primitives = {
  cylinders = (
    {
      x = 0.0;       # Base center X position
      y = 0.0;       # Base center Y position
      z = -5.0;      # Base center Z position
      r = 1.0;       # Radius
      height = 2.0;  # Height of the cylinder
      direction = {
        x = 0.0;     # Direction vector X
        y = 1.0;     # Direction vector Y
        z = 0.0;     # Direction vector Z
      };
      color = {
        r = 0;
        g = 255;
        b = 0;
      };
      material = {
        ambient = 0.1;
        diffuse = 0.7;
        specular = 0.2;
        shininess = 50.0;
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
      direction = {
        x = 1.0;     # Direction vector X
        y = -1.0;    # Direction vector Y
        z = -1.0;    # Direction vector Z
      };
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

## Complete Example
Here's a complete example of a scene config file with multiple primitives and directional lights:
```
# Default scene configuration file

camera = {
  resolution = {width = 1920; height = 1080;};
  position = {x = 0.0; y = 0.0; z = 0.0;};
  fieldOfView = 72.0;
};

primitives = {
  spheres = (
    {
      x = 0.0;
      y = 0.0;
      z = -5.0;
      r = 1.0;
      color = {r = 255; g = 51; b = 51;};
    },
    {
      x = 2.0;
      y = 0.0;
      z = -7.0;
      r = 1.0;
      color = {r = 51; g = 51; b = 255;};
    },
    {
      x = -2.0;
      y = 0.0;
      z = -7.0;
      r = 1.0;
      color = {r = 51; g = 255; b = 51;};
    },
    {
      x = 0.0;
      y = -2.0;
      z = -5.0;
      r = 1.0;
      color = {r = 255; g = 255; b = 51;};
    }
  );
  
  cylinders = (
    {
      x = -2.0;
      y = 1.0;
      z = -5.0;
      r = 0.4;
      height = 1.5;

      # Direction vector (axis)
      direction = {x = 0.0; y = 1.0; z = 0.0;};
      color = {r = 255; g = 128; b = 0;};
    },
    {
      x = 2.0;
      y = 1.0;
      z = -5.0;
      r = 0.4;
      height = 1.5;
      
      direction = {x = 0.3; y = 1.0; z = 0.2;};
      color = {r = 153; g = 51; b = 255;};
    }
  );
};

lights = {
  ambient = 0.1;
  diffuse = 0.7;

  directional = (
    {
      x = -1.0;
      y = -1.0;
      z = -1.0;
      color = {r = 255; g = 255; b = 255;};
      intensity = 1;
    },
    {
      x = 1.0;
      y = -0.5;
      z = -0.5;
      color = {r = 128; g = 128; b = 204;};
      intensity = 0.7;
    }
  );
};
```

## Implementation Details
### Builder Pattern
The `SceneBuilder` class implements the builder pattern to construct scene objects with a fluent interface:
```cpp
SceneBuilder builder;
builder.setCamera(camera)
       .setResolution(1280, 720)
       .addPrimitive(std::move(sphere))
       .addLight(std::move(light));
auto scene = builder.build();
```

### Factory Pattern
Multiple factory classes simplify object creation:
- `PrimitiveFactory` - Creates sphere and cylinder primitives
- `MaterialFactory` - Creates various material types
- `LightFactory` - Creates directional lights

### Multithreaded Rendering
The SFML renderer divides the image into tiles that are rendered in parallel for improved performance. The number of threads can be specified via command line or automatically determined.

### Design Patterns
The code makes use of several design patterns:
- **Builder Pattern**: For scene construction
- **Factory Pattern**: For object creation
- **Strategy Pattern**: For rendering strategies
- **Composite Pattern**: For scene graph management

## Notes
- The ray tracer uses a right-handed coordinate system
- The camera looks toward the negative Z axis by default
- PPM output format is a simple uncompressed image format that can be viewed with many graphics programs
- SFML rendering provides a real-time preview with the final image saved as PNG