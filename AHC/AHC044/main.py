import sys
import random
import time

# Read input
N = int(input().split()[0])  # Number of employees (100)
L = int(input().split()[1])  # Number of weeks (500000)
T = list(map(int, input().split()))  # Target assignments

start_time = time.time()
time_limit = 1.8  # Set time limit slightly under 2 seconds to ensure we have time to output

def calculate_error(assignments, targets):
    """Calculate total error between assignments and targets"""
    return sum(abs(assignments[i] - targets[i]) for i in range(len(targets)))

def simulate_assignments(a, b, weeks=L):
    """Simulate the cleaning duty assignment for L weeks"""
    assignments = [0] * N
    current = 0  # Start with employee 0
    
    for _ in range(weeks):
        assignments[current] += 1
        if assignments[current] % 2 == 1:  # Odd number of assignments
            current = a[current]
        else:  # Even number of assignments
            current = b[current]
    
    return assignments

def greedy_solution():
    """Generate a greedy solution"""
    # Initialize a and b randomly
    a = [random.randint(0, N-1) for _ in range(N)]
    b = [random.randint(0, N-1) for _ in range(N)]
    
    # Initial simulation
    assignments = simulate_assignments(a, b)
    best_error = calculate_error(assignments, T)
    best_a, best_b = a[:], b[:]
    
    # Try to improve the solution
    iterations = 0
    while time.time() - start_time < time_limit:
        iterations += 1
        
        # Choose a random employee and change their a_i or b_i
        employee = random.randint(0, N-1)
        is_a = random.choice([True, False])  # Whether to modify a or b
        
        # Save the old value
        if is_a:
            old_value = a[employee]
            a[employee] = random.randint(0, N-1)
        else:
            old_value = b[employee]
            b[employee] = random.randint(0, N-1)
        
        # Simulate with the new values
        new_assignments = simulate_assignments(a, b)
        new_error = calculate_error(new_assignments, T)
        
        # Accept if better, otherwise revert
        if new_error < best_error:
            best_error = new_error
            best_a, best_b = a[:], b[:]
        else:
            # Revert the change
            if is_a:
                a[employee] = old_value
            else:
                b[employee] = old_value
        
        # Every 1000 iterations, try something more drastic
        if iterations % 1000 == 0:
            # Randomly reset a segment of employees
            segment_start = random.randint(0, N-10)
            segment_len = random.randint(5, 10)
            for i in range(segment_start, min(segment_start + segment_len, N)):
                a[i] = random.randint(0, N-1)
                b[i] = random.randint(0, N-1)
    
    return best_a, best_b, best_error

# Try an improved approach: simulate shorter periods and extrapolate
def short_simulation_approach():
    """Use shorter simulations to quickly evaluate candidates"""
    # Initialize best values
    best_a = [random.randint(0, N-1) for _ in range(N)]
    best_b = [random.randint(0, N-1) for _ in range(N)]
    
    # Do a full simulation for the initial solution
    best_assignments = simulate_assignments(best_a, best_b)
    best_error = calculate_error(best_assignments, T)
    
    # For quick evaluations, use a shorter simulation period
    short_period = min(50000, L // 10)
    
    iterations = 0
    last_improvement_time = start_time
    
    while time.time() - start_time < time_limit:
        iterations += 1
        
        # Create a modified solution
        a = best_a[:]
        b = best_b[:]
        
        # Apply various mutation strategies
        mutation_type = random.randint(1, 3)
        
        if mutation_type == 1:
            # Single point mutation
            employee = random.randint(0, N-1)
            if random.random() < 0.5:
                a[employee] = random.randint(0, N-1)
            else:
                b[employee] = random.randint(0, N-1)
        elif mutation_type == 2:
            # Swap two employees' assignments
            emp1, emp2 = random.sample(range(N), 2)
            if random.random() < 0.5:
                a[emp1], a[emp2] = a[emp2], a[emp1]
            else:
                b[emp1], b[emp2] = b[emp2], b[emp1]
        else:
            # Segment modification
            segment_start = random.randint(0, N-5)
            segment_len = random.randint(2, 5)
            for i in range(segment_start, min(segment_start + segment_len, N)):
                if random.random() < 0.5:
                    a[i] = random.randint(0, N-1)
                else:
                    b[i] = random.randint(0, N-1)
        
        # Quick evaluation using shorter simulation
        short_assignments = simulate_assignments(a, b, short_period)
        # Scale up the assignments to estimate full simulation
        scaled_assignments = [count * (L / short_period) for count in short_assignments]
        short_error = calculate_error(scaled_assignments, T)
        
        # If it looks promising, do a full simulation
        if short_error < best_error * 1.1:  # Allow slightly worse solutions for exploration
            full_assignments = simulate_assignments(a, b)
            full_error = calculate_error(full_assignments, T)
            
            if full_error < best_error:
                best_error = full_error
                best_a, best_b = a[:], b[:]
                last_improvement_time = time.time()
        
        # If no improvement for a while, reset partially
        if time.time() - last_improvement_time > 0.3:
            # Reset 20% of the values
            reset_count = N // 5
            for _ in range(reset_count):
                idx = random.randint(0, N-1)
                if random.random() < 0.5:
                    best_a[idx] = random.randint(0, N-1)
                else:
                    best_b[idx] = random.randint(0, N-1)
            
            # Re-evaluate after reset
            best_assignments = simulate_assignments(best_a, best_b)
            best_error = calculate_error(best_assignments, T)
            last_improvement_time = time.time()
    
    return best_a, best_b, best_error

# Try a pattern-based approach
def pattern_based_approach():
    """Try to establish patterns that match target distribution"""
    best_a = [i for i in range(N)]  # Initialize with identity
    best_b = [i for i in range(N)]
    
    # Create initial cycles based on target distribution
    high_demand = sorted(range(N), key=lambda i: T[i], reverse=True)
    low_demand = sorted(range(N), key=lambda i: T[i])
    
    # Connect employees in cycles based on their demand
    for i in range(N):
        if T[i] > L/N:  # Higher than average demand
            # Connect to another high-demand employee
            idx = high_demand.index(i)
            best_a[i] = high_demand[(idx + 1) % len(high_demand)]
            # Mix with low demand occasional
            best_b[i] = low_demand[idx % len(low_demand)]
        else:
            # Connect mostly to low-demand employees
            idx = low_demand.index(i)
            best_a[i] = low_demand[(idx + 1) % len(low_demand)]
            best_b[i] = high_demand[idx % len(high_demand)]
    
    # Initial simulation
    best_assignments = simulate_assignments(best_a, best_b)
    best_error = calculate_error(best_assignments, T)
    
    # Local search to improve the solution
    iterations = 0
    while time.time() - start_time < time_limit:
        iterations += 1
        
        # Copy current best solution
        a = best_a[:]
        b = best_b[:]
        
        # Find an employee with high error
        assignments = simulate_assignments(a, b)
        errors = [abs(assignments[i] - T[i]) for i in range(N)]
        
        # Focus on employees with high error
        high_error_employees = sorted(range(N), key=lambda i: errors[i], reverse=True)
        
        for emp in high_error_employees[:5]:  # Focus on top 5 errors
            if assignments[emp] > T[emp]:
                # This employee gets too many assignments
                # Redirect their incoming assignments to others
                for i in range(N):
                    if a[i] == emp and random.random() < 0.5:
                        # Find someone who needs more assignments
                        targets = [j for j in range(N) if assignments[j] < T[j]]
                        if targets:
                            a[i] = random.choice(targets)
                    if b[i] == emp and random.random() < 0.5:
                        targets = [j for j in range(N) if assignments[j] < T[j]]
                        if targets:
                            b[i] = random.choice(targets)
            else:
                # This employee needs more assignments
                # Increase incoming assignments
                sources = random.sample(range(N), min(5, N))
                for src in sources:
                    if random.random() < 0.5:
                        a[src] = emp
                    else:
                        b[src] = emp
        
        # Evaluate new solution
        new_assignments = simulate_assignments(a, b)
        new_error = calculate_error(new_assignments, T)
        
        if new_error < best_error:
            best_error = new_error
            best_a, best_b = a[:], b[:]
    
    return best_a, best_b, best_error

# Try multiple approaches and take the best result
best_solution = None
best_error = float('inf')

# Time management: distribute time among approaches
remaining_time = time_limit - (time.time() - start_time)

if remaining_time > 0.4:
    a1, b1, error1 = greedy_solution()
    if error1 < best_error:
        best_solution = (a1, b1)
        best_error = error1

remaining_time = time_limit - (time.time() - start_time)
if remaining_time > 0.4:
    a2, b2, error2 = short_simulation_approach()
    if error2 < best_error:
        best_solution = (a2, b2)
        best_error = error2

remaining_time = time_limit - (time.time() - start_time)
if remaining_time > 0.4:
    a3, b3, error3 = pattern_based_approach()
    if error3 < best_error:
        best_solution = (a3, b3)
        best_error = error3

# Output the best solution
a, b = best_solution
for i in range(N):
    print(f"{a[i]} {b[i]}")