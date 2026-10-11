https://seedwind-living-earth-lab.tealbay4.chatgpt.site/ -- our (sim)
🌱 SEEDWIND — Living Earth Lab
Where nature meets tomorrow. An experimental environmental mapping and aerial seed-deployment simulation project exploring how geospatial data, weather conditions, and autonomous flight concepts could support ecological restoration in Kenya.

![Project](https://img.shields.io/badge/Project-HackPHS-00a896) ![Status](https://img.shields.io/badge/Status-Experimental-orange)

🌍 Overview
SEEDWIND is an interactive environmental exploration and flight simulation dashboard designed around the Kenyan landscape. It combines map visualization, environmental data, and simulated aerial missions to explore how technology might help identify potential areas for ecological restoration.

The project brings together a web-based dashboard and hardware-oriented control code in an experimental prototype.

✨ Features
Interactive mapping: Explore locations in Kenya using satellite, terrain, and street map views.
Environmental visualization: View terrain and soil-proxy layers alongside atmospheric wind information.
Site selection: Choose deployment sites, focus the map on an area, or select a destination manually.
Flight simulation: Explore simulated aerial mission states, flight altitude, and wind conditions.
Seed-deployment tracking: Monitor simulated seed deployment and survey coverage.
Weather forecasting: Examine forecast data and potential wind conditions for simulated flight planning.
Configurable simulation: Adjust simulation speed and the minimum environmental suitability proxy score.
Hardware exploration: Includes Arduino-oriented camera and motor control code, alongside Wi-Fi access point files.
🖥️ Live Demo
Launch SEEDWIND

Explore the dashboard to interact with the map, inspect environmental layers, and experiment with the mission simulation.

🛠️ Built With
HTML, CSS, and JavaScript — interactive dashboard and simulation interface.
Leaflet.js — interactive mapping.
Open-Meteo — weather and forecast data.
Arduino/C++ — hardware-oriented control code.
GeoJSON and CSV — geospatial analysis and simulation data.
🚀 Getting Started
Option 1: Use the live demo
Visit the SEEDWIND web application in a modern web browser.

Option 2: Run locally
Clone the repository:
   git clone https://github.com/theMakermansdas12/Hackphs-project--Certfied-scuffed.git
Navigate into the project directory:
   cd Hackphs-project--Certfied-scuffed
Open SEEDWIND-AERO-GLASS.html in a modern web browser.
For a more consistent local development setup, serve the directory using a local HTTP server:
   python -m http.server 8000
Open http://localhost:8000/SEEDWIND-AERO-GLASS.html.
Note: Internet access is required for external map tiles, weather data, and externally hosted libraries. Some features may not work if those services are unavailable.

📁 Repository Structure
Hackphs-project--Certfied-scuffed/
├── Camera_Control.ino          # Arduino camera control
├── Motor_Controls/              # Motor control files
├── WiFiAccessPoint/             # Wi-Fi access point files
├── libraries/                   # Supporting libraries
├── SEEDWIND-AERO-GLASS.html      # Interactive web dashboard
├── seedwind-analysis.geojson    # Geospatial analysis data
├── seedwind-flight-simulation.csv # Flight simulation data
└── README.md                    # Project documentation
🧭 How to Explore
Launch the dashboard.
Select a deployment site or navigate to a location on the map.
Switch between satellite, terrain, and street map views.
Enable or disable environmental layers to explore the available information.
Adjust simulation settings and observe the simulated mission.
Review the flight, wind, seed-deployment, and survey-coverage indicators.
🔬 Important Limitations
SEEDWIND is an experimental research and simulation prototype, not a validated environmental assessment or operational flight-control system.

Environmental suitability scores use experimental proxy inputs and should not be treated as verified planting recommendations.
Simulated seed counts and survey coverage do not establish real-world deployment or restoration outcomes.
Weather forecasts are not a substitute for professional flight-safety assessments.
Real-world planting requires ecological validation, suitable native species, and appropriate land-use permission.
Hardware control code should be reviewed and tested independently before connecting it to physical equipment.
🔮 Future Improvements
Potential directions for further development include:

Integrating validated ecological and soil datasets.
Improving environmental suitability models.
Adding mission-planning and simulation visualizations.
Connecting hardware telemetry to the dashboard.
Expanding deployment-site analysis and reporting.
Improving reliability when external data sources are unavailable.
🤝 Contributing
Contributions, suggestions, and bug reports are welcome.

Fork the repository.
Create a feature branch.
Make and test your changes.
Submit a pull request describing your improvements.
📄 License
No license is specified here. Check the repository for licensing information before redistributing or reusing the project's code and assets.

Built for HackPHS. Exploring the intersection of technology, aerial systems, and ecological restoration.
