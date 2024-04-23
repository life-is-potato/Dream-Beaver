import os
import time
import threading
from googlesearch import search

def initialize_files(target_filename, results_filename):
    # Initialize target file to empty
    with open(target_filename, "w") as target_file:
        target_file.truncate(0)
    
    # Initialize results file to empty
    with open(results_filename, "w") as results_file:
        results_file.truncate(0)

def check_file_modification(filename, results_filename):
    # Get the initial modification time of the file
    original_modification_time = os.path.getmtime(filename)
    
    while True:
        # Wait for a bit (you can change this duration based on your requirement)
        time.sleep(2)
        
        # Get the current modification time
        current_modification_time = os.path.getmtime(filename)
        
        # Compare modification times
        if original_modification_time != current_modification_time:
            print("File modified. Searching content on Google...")
            
            # Clear the content of the results file
            with open(results_filename, "w") as result_file:
                result_file.truncate(0)
            
            with open(filename, "r") as file:
                file_content = file.read()
                search_results = search(file_content + "offers", num=6)
                print("Top 6 search results:")
                # Append search results to the result file
                with open(results_filename, "a") as result_file:
                    for idx, result in enumerate(search_results, start=1):
                        result_file.write(f"{idx}. {result}\n")
                        print(f"{idx}. {result}")
                        if idx == 6:
                            break

            # Update original modification time for further monitoring
            original_modification_time = current_modification_time

def user_interaction():
    print("Monitoring for file modification...")
    while True:
        time.sleep(1)  # Just to keep the thread running

def main():
    target_filename = r"target.txt"
    results_filename = r"results.txt"
    
    # Initialize target.txt and results.txt to empty
    initialize_files(target_filename, results_filename)
    
    # Create a thread for file monitoring
    file_monitoring_thread = threading.Thread(target=check_file_modification, args=(target_filename, results_filename))
    file_monitoring_thread.start()
    
    # Run user interaction in the main thread
    user_interaction()

if __name__ == "__main__":
    main()
