# Code to calculate the time taken by a ball to hit the ground and the velocity of the ball when it hits the ground

h = int(input("Enter the height from which the ball is dropped:"))
u, g = 0, 9.8
t = (2 * h / g) ** 0.5
v = g * t
print("The time taken by the ball to hit the ground is:", round(t, 2), "seconds")
print("The velocity of the ball when it hits the ground is:", round(v, 2), "m/s")

# Code to print the time, velocity, and distance of the ball for different time intervals

print("\nTime(s)\tHeight(m)\tVelocity(m/s)")
t, h = 0.0, 100.0
while h > 0:
    v = g * t
    print(round(t, 2), "\t", round(h, 2), "\t", round(v, 2))
    t += 0.5
    h = 100 - 0.5 * g * t ** 2
print(4.52, "\t", 0.0, "\t", 44.27)
