import random

# Set the grid size
grid_size = 32

# Create an empty grid filled with dots
grid = [['.' for _ in range(grid_size)] for _ in range(grid_size)]

# Choose the number of random letters to insert
num_letters = 100  # Change this as needed

# Define the letters to randomly choose from
letters = ["C", "c", "d", "B"]

# Add the letters at random positions
for _ in range(num_letters):
    x, y = random.randint(0, grid_size - 1), random.randint(0, grid_size - 1)
    grid[x][y] = random.choice(letters)

# Print the grid
for row in grid:
    print(''.join(row))