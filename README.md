# Satellite Orbit Simulator 🚀

A simple satellite orbit simulation engine built from scratch to explore orbital mechanics, numerical integration, and physics-based visualization.

The project uses a **C++ core** for accurate orbital propagation and a **Python visualization layer** to animate the resulting trajectories in 3D.

---

## ✨ Features

- Earth-centered inertial (ECI) frame simulation  
- Newtonian two-body gravitational model  
- Velocity-Verlet integration for numerical stability  
- Supports circular and elliptical orbits  
- Arbitrary orbital inclination  
- Energy and angular momentum conservation checks  
- CSV-based data pipeline  
- 3D orbit animation using Python & Matplotlib  
- Scales from LEO to GEO orbits  

---

## 🧠 Physics Model

The satellite motion is governed by the classical two-body equation:

\[
\ddot{\vec r} = -\mu \frac{\vec r}{r^3}
\]

Where:
- \(\vec r\) is the position vector from Earth’s center  
- \(\mu = GM\) is Earth’s gravitational parameter  

The simulation validates correctness by tracking:
- **Specific mechanical energy**
- **Specific angular momentum**

Both remain conserved throughout the simulation (within numerical precision).

---

## 🛠️ Project Structure

```text
orbit-propagator/
├──orbit_cal.cpp        # C++ orbital propagator
├──data.csv             # Simulation output
├──visualize.py         # Python 3D animation
└──README.md
```
## 🚀 How It Works
1. C++ Simulation (Physics Core)

User specifies orbit type, altitude, inclination, timestep, and duration

The simulator computes satellite motion using Velocity-Verlet integration

Position, velocity, energy, and angular momentum are written to a CSV file

Compile and run:
```bash
g++ orbit_cal.cpp -o orbit_cal
./orbit_cal
```
2. Python Visualization

Reads the generated CSV file

Renders Earth as a 3D sphere

Animates the satellite trajectory and trail

Run:
```bash
python visualize.py
```
## 📊 Output Data Format

The simulation exports the following CSV columns:
```

t, x, y, z, vx, vy, vz, r, E, h
```

Where:

Position is in meters

Velocity is in m/s

Time is in seconds

Energy and angular momentum are specific quantities (per unit mass)

## 📈 Validation

Correctness is verified by:

Constant specific mechanical energy

Constant angular momentum magnitude

Stable orbital planes for inclined orbits

These checks ensure physically accurate propagation.

## 🧪 Tested Scenarios

Low Earth Orbit (LEO)

Highly inclined orbits

Elliptical orbits

Geostationary-like orbits (GEO scale)

## 🔮 Possible Extensions

Earth rotation and ground tracks

J2 perturbation (oblateness effects)

Atmospheric drag

Multi-body gravity (Moon, Sun)

Adaptive timestep

Multi-satellite simulations

## 🎯 Motivation

This project was built as an exploratory exercise to deepen understanding of:

Orbital mechanics

Numerical integration techniques

Physics-based simulation design

Separation of computation and visualization

## 📌 Notes

Earth is modeled as a point mass (no perturbations)

Satellite mass is ignored (two-body approximation)

Visualization uses real-world scale (LEO orbits appear very close to Earth)

## Snapshot of Output
![WhatsApp Image 2026-02-08 at 1 52 37 AM](https://github.com/user-attachments/assets/8bef18d9-e5b2-4e62-9bf2-ca051baed1f7)
