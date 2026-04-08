from PIL import Image
import os

# Loop through all files in the current folder
for filename in os.listdir('.'):
    if filename.endswith(".png"):
        img = Image.open(filename)
        
        # Calculate new size (Scaling up by 4x. Change this number if you need a different size!)
        new_width = img.width * 2
        new_height = img.height * 2
        
        # Resize using NEAREST to keep pixel art crisp
        new_img = img.resize((new_width, new_height), Image.NEAREST)
        
        # Save it (overwrites the old file)
        new_img.save(filename)
        print(f"Successfully resized {filename} to {new_width}x{new_height}")