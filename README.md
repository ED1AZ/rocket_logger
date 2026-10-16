# DELIVERABLE 1
I used the same inputs as the example (z0 = 0, v0 = 0, 50 fuel steps, a_thrust = 15 m/s^2, dt = 0.1 s, max steps = 300). 

50 fuel steps * 0.1 = 5 seconds of fuel

Since a_thrust > g, the rocket lifts off and the fuel burns for 5 seconds. It reaches an apex of about 99.2 m and falls back to the ground. The max step cap of 300 is large enough to cover the full flight, which lands at 121 steps (12.1 s).

![Alt text](docs/screenshot.png)

# DELIVERABLE 2
I used the same inputs as the example (z0 = 0, v0 = 0, 50 fuel steps, a_thrust = 15 m/s^2, dt = 0.1 s, max steps = 300). This allowed me to verify my results with the previous deliverable.

I added a PRELAUNCH state in run_rocket_state() to check if rocket should be able to lift off, allowing me to keep the loop condition (while state != FLIGHT_LANDED). Then, other states are updated by having a state change condition inside the case statement. That is, if the vehicle is in FLIGHT_ASCENT case, it checks the fuel and velocity to see if it is coasting, then changes to FLIGHT_COASTING. 

update_sensor_sample() is basically the physics logic from the previous deliverable. Timestamp is incremented within.

update_telemetry_state collects values from sensor and updates velocity/altitude.

![Alt text](docs/screenshot2.png)
