<p align="center">
  <a href="#license">
    <img src="Resources/Branding/BannerSmall.png" alt="Logo" width=300 height=180>
  </a>

<h3 align="center">kraster</h3>

  <p align="center">
    Kraster Software Renderer
    <br>
    <a href="https://github.com/krnl32/kraster/issues/new?labels=bug">Report bug</a>
    ·
    <a href="https://github.com/krnl32/kraster/issues/new?labels=feature">Request feature</a>
  </p>
</p>

## About

Kraster Software Renderer.

# Features

- Full 3D rendering pipeline:
	- Model -> World -> View -> Projection transforms

- Custom math library:
	- Vec2 / Vec3 / Vec4 operations
	- 4x4 matrix transforms (scale, rotate, translate, look-at, perspective)

- Perspective projection with homogeneous divide

- Depth buffering (Z-buffer)

- Backface culling (toggleable)

- Multiple render modes:
	- Wireframe
	- Wireframe + vertices
	- Filled triangles
	- Filled + wire overlay
	- Textured
	- Textured + wire overlay

- Triangle rasterization:
	- Scanline rasterization
	- Barycentric coordinate interpolation

- Perspective-correct texture mapping

- Basic directional lighting (Lambert-style intensity)

- OBJ mesh loading (vertices, UVs, faces)

- Texture loading (via stb_image)

- Camera system:
	- Position + direction
	- Yaw / pitch rotation
	- Free movement controls (WASD + vertical + rotation)

## Build

Please read through our [building guidelines](https://github.com/krnl32/kraster/blob/master/BUILDING.md).

## Bugs and feature requests

Have a bug or a feature request? Please first read
the [issue guidelines](https://github.com/krnl32/kraster/blob/master/CONTRIBUTING.md) and search for existing and closed
issues. If your problem or idea is not addressed
yet, [please open a new issue](https://github.com/krnl32/kraster/issues/new).

## Contributing

Please read through our [contributing guidelines](https://github.com/krnl32/kraster/blob/master/CONTRIBUTING.md).
Included
are directions for opening issues, coding standards, and notes on development.

## Authors

- [**krnl32**](https://github.com/krnl32)

## License

kraster is Licensed under the [GPL-3 License](https://github.com/krnl32/kraster/blob/master/COPYING.txt).
