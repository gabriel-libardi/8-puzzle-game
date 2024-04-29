from PIL import Image

def split_image(image_path, output_path):
    # Open the image
    img = Image.open(image_path)
    width, height = img.size
    
    # Define grid dimensions
    rows = 3
    cols = 3
    tile_width = width // cols
    tile_height = height // rows
    i = 1

    # Iterate over each tile
    for y in range(rows):
        for x in range(cols):
            # Crop tile from original image
            left = x * tile_width
            top = y * tile_height
            right = (x + 1) * tile_width
            bottom = (y + 1) * tile_height
            tile = img.crop((left, top, right, bottom))

            # Save tile as a new image
            tile.save(f"tile_{i}.png")
            i += 1

if __name__ == "__main__":
    # Input image file name
    image_file = input("Enter the image file name: ")
    
    # Output directory for tiles
    output_dir = "output_tiles"
    
    # Load the image and split into tiles
    split_image(image_file, output_dir)
