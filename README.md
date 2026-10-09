# rocket_logger
I used the same inputs as the example (z0 = 0, v0 = 0, 50 fuel steps, a_thrust = 15 m/s^2, dt = 0.1 s, max steps = 300). 

50 fuel steps * 0.1 = 5 seconds of fuel

Since a_thrust > g, the rocket lifts off and the fuel burns for 5 seconds. It reaches an apex of about 99.2 m and falls back to the ground. The max step cap of 300 is large enough to cover the full flight, which lands at 121 steps (12.1 s).

![Alt text](docs/screenshot.png)
