# Image Filtering

Simple C project to apply different filters to BMP images. The different filters are grayscale, sepia, reflection, and blur.

## Usage

To use, compile and run the executable with the following command

```./filter -[flag] [input] [output]```

Where:
- `[flag]` is one of the following:
    - `g` for grayscale
    - `s` for sepia
    - `r` for reflect
    - `b` for blur
- `[input]` is path to the input BMP file
- `[output]` is where the filtered image will be saved

## Example

Original Image:

![Original](images/lena.bmp)

Filtered Images:

- Grayscale:

  ![Grayscale](filtered_images/grayscale.bmp)

- Sepia:

  ![Sepia](filtered_images/sepia.bmp)

- Reflect:

  ![Reflect](filtered_images/reflect.bmp)

- Blur:

  ![Blur](filtered_images/blur.bmp)

## Building the Project

Compiled using clang and make
