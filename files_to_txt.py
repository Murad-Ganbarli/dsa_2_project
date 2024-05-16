import os

def find_files(directory, output_file):
    with open(output_file, 'w', encoding='utf-8') as f:
        for root, dirs, files in os.walk(directory):
            for file in files:
                #if not endswith ['.exe', '.o', '.py'] read:
                if file.endswith('.c') or file.endswith('.h'):
                    filepath = os.path.join(root, file)
                    f.write("=" * 50 + '\n')
                    f.write("File: {}\n".format(filepath))
                    
                    f.write("=" * 50 + '\n')
                    with open(filepath, 'r') as java_file:
                        content = java_file.read()
                        f.write(content)
                        f.write("\n\n")

# Specify the directory to search
directory_to_search = "C:/Users/murad/Programming/DSA_2/Project/"

# Specify the output file path
output_file_path = 'files_with_content.txt'

# Call the function to find Java files and write to the output file
find_files(directory_to_search, output_file_path)

print("Files found and their content written to", output_file_path)
