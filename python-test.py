import subprocess
import time
import matplotlib.pyplot as plt
import pcre2

# Initialize lists to store values of i and corresponding execution times
i_values = []
execution_times = []

# Loop from 1 to 1000
for i in range(1, 1000):
    print(i)
    # Construct the pattern 'ba' repeated i times
    pattern = 'b'
    aaa = 'a' * 100 * i
    pattern += aaa
    
    # Prepare the command to run in bash
    command = f"orpheus 'b(?:a(?<=ba*))*' '{pattern}'"
    
    # Record the start time
    start_time = time.time()
    
    # Execute the command
    try:
        subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except subprocess.CalledProcessError as e:
        print(f"Command failed with error: {e}")
        continue
    
    # Record the end time
    end_time = time.time()
    
    # Calculate the execution time
    execution_time = end_time - start_time
    
    # Append the values to the lists
    i_values.append(i*100)
    execution_times.append(execution_time)

# Plot the execution times
plt.figure(figsize=(10, 6))
plt.plot(i_values, execution_times, marker='o')
plt.xlabel('Lenght of string ba^n')
plt.ylabel('Execution Time (seconds)')
plt.title('Execution Time of b(?:a(?<=ba*))* on ba^n')
plt.grid(True)
plt.show()

