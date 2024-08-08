
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

### Boards

- [`WT32 SC01`](resources/WT32-SC01-datasheet.pdf)
- [`WT32 SC01 Plus Datasheet`](resources/ZX3D50CE02S-USRC-4832+Datasheet.pdf)

#### Screenshots

![w10m](screenshots/windows-10-mobile.png?raw=true "w10m")



### SquareLine Studio

Squareline studio project has been included in the repository, this however may not reflect the current state of the project due to limitations in the free tier.

### Stargazers

[`stars.py`](support/stars.py) script generates [`stars.h`](src/ui/stars.h) with a list of the current stargazers. This will be visible in the UI on the 'Stars app'.
The file will be regenerated after 24 hrs from the last modification. To regenerate immediately, delete [`stars.h`](src/ui/stars.h) and build the project

![Stars](screenshots/stars.png?raw=true "stars")