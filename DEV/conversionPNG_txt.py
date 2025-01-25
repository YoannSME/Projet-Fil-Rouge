from PIL import Image

# Load the uploaded image
image_path_max_600 = "/mnt/data/image.png"
image_max_600 = Image.open(image_path_max_600)

# Resize the image to fit within 600x600 while maintaining aspect ratio
image_max_600.thumbnail((600, 600))

# Get the new dimensions after resizing
width_max_600, height_max_600 = image_max_600.size

# Convert the image to RGB (if not already)
image_max_600 = image_max_600.convert("RGB")

# Extract RGB values as a list of tuples
rgb_data_max_600 = list(image_max_600.getdata())

# Create separate matrices for red, green, and blue components
red_matrix_max_600 = []
green_matrix_max_600 = []
blue_matrix_max_600 = []

for y in range(height_max_600):
    row_data = rgb_data_max_600[y * width_max_600:(y + 1) * width_max_600]
    red_matrix_max_600.append([r for r, _, _ in row_data])
    green_matrix_max_600.append([g for _, g, _ in row_data])
    blue_matrix_max_600.append([b for _, _, b in row_data])

# Write the data to a text file with the specified format
output_path_max_600 = "/mnt/data/image_resized_600x600.txt"
with open(output_path_max_600, "w") as file:
    # Write dimensions and the number of matrices as the first line
    file.write(f"{height_max_600} {width_max_600} 3\n")

    # Write the red matrix
    for row in red_matrix_max_600:
        file.write(" ".join(map(str, row)) + "\n")

    # Write the green matrix
    for row in green_matrix_max_600:
        file.write(" ".join(map(str, row)) + "\n")

    # Write the blue matrix
    for row in blue_matrix_max_600:
        file.write(" ".join(map(str, row)) + "\n")

output_path_max_600
