#include <math.h>
#include <stdint.h>

#include "util.h"

int max(int num, int bound);
int min(int num, int bound);
uint8_t round_sepia(float sepia_val);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  // Loop over all pixels
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // Take the avereage of rgb
      uint8_t average = round(
          (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) /
          3.0);

      // Update pixel values
      image[i][j].rgbtBlue = average;
      image[i][j].rgbtGreen = average;
      image[i][j].rgbtRed = average;
    }
  }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
  // Loop over all pixels
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      uint8_t original_red = image[i][j].rgbtRed;
      uint8_t original_green = image[i][j].rgbtGreen;
      uint8_t original_blue = image[i][j].rgbtBlue;

      // Compute sepia values
      float sepia_red =
          0.393 * original_red + 0.769 * original_blue + 0.189 * original_blue;
      float sepia_green =
          0.349 * original_red + 0.686 * original_green + 0.168 * original_blue;
      float sepia_blue =
          0.272 * original_red + 0.534 * original_green + 0.131 * original_blue;

      // Update pixels with sepia values
      image[i][j].rgbtRed = round_sepia(sepia_red);
      image[i][j].rgbtGreen = round_sepia(sepia_green);
      image[i][j].rgbtBlue = round_sepia(sepia_blue);
    }
  }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE copy_px;
  for (int i = 0; i < height; i++) {
    // Reflect pixels across row of image
    for (int j = 0, n = width / 2; j < n; j++) {
      copy_px = image[i][j];
      image[i][j] = image[i][width - j - 1];
      image[i][width - j - 1] = copy_px;
    }
  }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  // Create copy of the image
  RGBTRIPLE copy[height][width];
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      copy[i][j] = image[i][j];
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // Create image bounds
      // Each pixel will be averaged with surrounding
      // pixels up to a 3x3 grid
      int left = max(j - 1, 0);
      int top = max(i - 1, 0);
      int right = min(j + 1, width - 1);
      int bottom = min(i + 1, height - 1);

      // These used to average pixel values
      int divisor = 0;
      float sum_r = 0;
      float sum_g = 0;
      float sum_b = 0;

      // Loop over surrounding pixels adjacent to current pixel
      for (int y = top; y <= bottom; y++) {
        for (int x = left; x <= right; x++) {
          sum_r += copy[y][x].rgbtRed;
          sum_g += copy[y][x].rgbtGreen;
          sum_b += copy[y][x].rgbtBlue;
          divisor++;
        }
      }

      // Update pixels to create blur
      image[i][j].rgbtRed = (uint8_t)round(sum_r / divisor);
      image[i][j].rgbtGreen = (uint8_t)round(sum_g / divisor);
      image[i][j].rgbtBlue = (uint8_t)round(sum_b / divisor);
    }
  }
}

uint8_t round_sepia(float sepia_val) {
  if (sepia_val > 255) {
    return 255;
  }
  return round(sepia_val);
}

int max(int num, int bound) {
  if (num < bound) {
    return bound;
  }
  return num;
}

int min(int num, int bound) {
  if (num > bound) {
    return bound;
  }
  return num;
}
