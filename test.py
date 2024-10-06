# Efficiently handle a large number of integers by processing the file in chunks
def sort_large_file(input_file, output_file):
    # Open the input file and read all numbers
    with open(input_file, 'r') as file:
        # Read the file, convert to integers and store them in a list
        numbers = [int(line.strip()) for line in file]

    # Sort the list of numbers
    numbers.sort()

    # Open the output file and write the sorted numbers
    with open(output_file, 'w') as file:
        for number in numbers:
            file.write(f"{number}\n")
            

def compare_files(file1, file2, output_file):
    # Read numbers from both files into sets for comparison
    with open(file1, 'r') as f1:
        numbers1 = set(int(line.strip()) for line in f1)
        
    with open(file2, 'r') as f2:
        numbers2 = set(int(line.strip()) for line in f2)
    
    # Find excess numbers in file1 that are not in file2
    excess_numbers = numbers1 - numbers2
    
    # Get the count of excess numbers
    excess_count = len(excess_numbers)
    
    # Write the excess numbers and count to the output file
    with open(output_file, 'w') as out_file:
        for number in sorted(excess_numbers):
            out_file.write(f"{number}\n")
        out_file.write(f"\nCount of excess numbers: {excess_count}\n")
    
    print(f"Excess numbers written to {output_file}. Count: {excess_count}")

# File paths
file2 = 'data3.txt'
file1 = 'merged_output.txt'
output_file = 'excess-output.txt'

# Compare the files and find excess numbers
compare_files(file1, file2, output_file)


# # Define file paths
# input_file = 'data3.txt'
# output_file = 'test-output.txt'

# # Sort the large file
# sort_large_file(input_file, output_file)
