
# windows-10-mobile-lvgl

An LVGL project to showcase the nostalgic Windows 10 Moblie user interface.


#### Features
- Start Screen with 'Live tiles'
- Lock Screen
- Navigation Bar
- Status Bar
- Settings 
    - Personalization
- Cortana

#### Screenshots

![Start](screenshots/start.png?raw=true "start")
![Lockscreen](screenshots/lockscreen.png?raw=true "lockscreen")
![Panel](screenshots/panel.png?raw=true "panel")
![Cortana](screenshots/cortana.png?raw=true "cortana")
![Settings](screenshots/settings.png?raw=true "settings")



### SquareLine Studio

Squareline studio project has been included in the repository, this however may not reflect the current state of the project due to limitations in the free tier.

### Stargazers

[`stars.py`](support/stars.py) script generates [`stars.h`](src/ui/stars.h) with a list of the current stargazers. This will be visible in the UI on the 'Stars app'.
The file will be regenerated after 24 hrs from the last modification. To regenerate immediately, delete [`stars.h`](src/ui/stars.h) and build the project