import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

data = np.loadtxt("data.csv", delimiter=",", skiprows=1)

t = data[:, 0]
x = data[:, 1]
y = data[:, 2]
z = data[:, 3]

R_EARTH = 6371e3  # meters

u = np.linspace(0, 2*np.pi, 60)
v = np.linspace(0, np.pi, 60)

earth_x = R_EARTH * np.outer(np.cos(u), np.sin(v))
earth_y = R_EARTH * np.outer(np.sin(u), np.sin(v))
earth_z = R_EARTH * np.outer(np.ones_like(u), np.cos(v))


fig = plt.figure(figsize=(9, 9))
ax = fig.add_subplot(111, projection="3d")

ax.set_title("Satellite Orbit Simulation")

ax.set_xlabel("X (m)")
ax.set_ylabel("Y (m)")
ax.set_zlabel("Z (m)")


max_range = np.max(np.sqrt(x**2 + y**2 + z**2))
ax.set_xlim(-max_range, max_range)
ax.set_ylim(-max_range, max_range)
ax.set_zlim(-max_range, max_range)

ax.set_box_aspect([1, 1, 1])

ax.plot_surface(
    earth_x, earth_y, earth_z,
    color="royalblue", alpha=0.25, linewidth=0
)

ax.plot_wireframe(
    earth_x, earth_y, earth_z,
    color="black", linewidth=0.3, alpha=0.2
)

orbit_line, = ax.plot([], [], [], color="red", lw=1.5, label="Orbit Path")
satellite,  = ax.plot([], [], [], "ro", markersize=6, label="Satellite")

ax.legend()

def update(frame):
    # trail
    orbit_line.set_data(x[:frame], y[:frame])
    orbit_line.set_3d_properties(z[:frame])

    # satellite (single point must be sequence)
    satellite.set_data([x[frame]], [y[frame]])
    satellite.set_3d_properties([z[frame]])

    return orbit_line, satellite
STEP=10
frames = range(0, len(t), STEP)
ani = FuncAnimation(
    fig,
    update,
    frames,
    interval=20,   # ms between frames
    blit=True
)

plt.show()