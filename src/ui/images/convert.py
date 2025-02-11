import re
import os
import glob

def read_c_array(input_file):
    """Reads the C array from the input file and extracts the hex data."""
    with open(input_file, "r") as f:
        content = f.read()

    # Use a regex to find the array of hex values
    # This matches patterns like 0xFF, 0x12, etc.
    hex_values = re.findall(r'0x[0-9A-Fa-f]{2}', content)
    
    # Convert the hex values to integers
    image_data = [int(value, 16) for value in hex_values]
    
    return image_data, "LV_IMG_CF_TRUE_COLOR_ALPHA" in content, "LVGL_9 compatible" in content, "LV_COLOR_DEPTH" in content

def separate_rgb565_and_alpha(image_data):
    rgb565_array = []
    alpha_array = []
    
    # Loop through the image data, processing 3 bytes (RGB565 + alpha) per pixel
    for i in range(0, len(image_data), 3):
        rgb565 = image_data[i:i+2]  # 2 bytes for RGB565
        alpha = image_data[i+2]     # 1 byte for alpha
        
        # Append to corresponding arrays
        rgb565_array.append(rgb565)
        alpha_array.append(alpha)
    
    return rgb565_array, alpha_array

def exract_rgb565(image_data):
    rgb565_array = []
    
    # Loop through the image data, processing 2 bytes (RGB565) per pixel
    for i in range(0, len(image_data), 2):
        rgb565 = image_data[i:i+2]  # 2 bytes for RGB565
        # Append to corresponding arrays
        rgb565_array.append(rgb565)
    
    return rgb565_array

def write_c_code(output_file, rgb565_data, alpha_data):

    with open(output_file, "r") as f:
        content = f.read()
    
    pattern = re.compile(r"\[\]\s*=\s*\{.*?\};", re.DOTALL)

    hex_str = ""
    x = 0
    for rgb in rgb565_data:
        # Combine the two bytes into a single uint16_t value
        value = (rgb[0] << 8) | rgb[1]
        
        hex_str = hex_str + (f"0x{rgb[1]:02X},")
        hex_str = hex_str + (f"0x{rgb[0]:02X},")
        x = x + 1
        if x % 48 == 0:
            hex_str = hex_str + ("\n")
    hex_str = hex_str + ("\n\n")
    
    x = 0

    # Write the Alpha data as a C array
    for alpha in alpha_data:
        hex_str = hex_str + (f"0x{alpha:02X},")
        x = x + 1
        if x % 96 == 0:
            hex_str = hex_str + ("\n")
    hex_str = hex_str + ("\n")
    # hex_str = "test"

    new_content = pattern.sub(f"[] = {{\n{hex_str}\n}}; // LVGL_9 compatible", content)
    # print(new_content)
    new_content = new_content.replace("LV_IMG_CF_TRUE_COLOR_ALPHA", "LV_COLOR_FORMAT_NATIVE_WITH_ALPHA").replace("LV_IMG_CF_TRUE_COLOR", "LV_COLOR_FORMAT_NATIVE").replace(".header.always_zero = 0,", ".header.magic = LV_IMAGE_HEADER_MAGIC,").replace(".header.reserved = 0,", "")

    with open(output_file, "w") as f:
        f.write(new_content)

def process_c_array(input_file, output_file):
    # Step 1: Read the C array and extract hex data
    image_data, has_alpha, lvgl_9, face_file = read_c_array(input_file)
    
    if not lvgl_9 and not face_file:
        # Step 2: Separate the RGB565 and alpha channels
        # 
        if has_alpha:
            print("has alpha channel")
            rgb565_data, alpha_data = separate_rgb565_and_alpha(image_data)
        else:
            print("no alpha channel")
            rgb565_data = exract_rgb565(image_data)
            alpha_data = []
        
        # Step 3: Write the data to a new C file
        write_c_code(output_file, rgb565_data, alpha_data)
    else:
        print("already converted")


def process_all_c_files(directory):
    """Processes all .c files in a directory and replaces array content."""
    
    # Find all .c files in the directory and its subdirectories
    c_files = glob.glob(os.path.join(directory, '**', '*.c'), recursive=True)
    
    # Iterate through each file and replace the array content
    for file_path in c_files:
        print(file_path)
        process_c_array(file_path, file_path)

# Example usage
directory = "./"  # The folder containing .c files

# put this file in your images folder that contains the c array images.
# run python convert.py

# Process all .c files in the folder
process_all_c_files(directory)
# Example usage
# input_file = "face_75_2_dial_dial_img_0_1024.c"  # The input C file with the existing uint8_t array
# output_file = "image_separated.txt"  # The output C file

# process_c_array(input_file, input_file)