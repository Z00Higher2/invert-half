import numpy as np

MAX_H = 512
MAX_W = 512

def read_image():
    image = []
    height = 0
    width = 0

    with open("inImage.pgm", 'r') as instr:
        # Read and validate the PGM file header
        assert instr.readline().strip() == 'P2'

        # Skip any comments in the file
        while instr.peek(1) == '#':
            instr.readline()

        # Read image width, height, and maximum pixel value
        width, height = map(int, instr.readline().split())
        assert width <= MAX_W
        assert height <= MAX_H
        max_val = int(instr.readline())
        assert max_val == 255

        # Read pixel values into the image list
        for _ in range(height):
            row = list(map(int, instr.readline().split()))
            image.append(row)

    return image, height, width

def write_image(image, height, width):
    with open("outImage.pgm", 'w') as ostr:
        # Write the PGM file header
        ostr.write("P2\n")
        ostr.write(f"{width} {height}\n")
        ostr.write("255\n")

        # Write pixel values to the output file
        for row in range(height):
            ostr.write(" ".join(map(str, image[row])))
            ostr.write('\n')

def main():
    img, h, w = read_image()
    out = np.zeros((MAX_H, MAX_W), dtype=int)

    # Perform the image processing (negate pixel values and mirror horizontally)
    for row in range(h):
        for col in range(w):
            out[row, col] = 255 - img[row][col]

        for col in range(w // 2 - 1, -1, -1):
            out[row, w - 1 - col] = img[row][col]

    # Write the processed image to the output file
    write_image(out, h, w)

if __name__ == "__main__":
    main()
