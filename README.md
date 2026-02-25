# lost on the highest peak

Code repository for an interactive sound installation — 8 Arduino microcontrollers with touch sensors and two IMUs attached to 8 swings in a large industrial space, controlling sound interactively via vvvv and [VVVV.Audio](https://github.com/tebjan/VVVV.Audio).

[![lost on the highest peak - David Rittershaus](https://vumbnail.com/190703905.jpg)](https://vimeo.com/190703905)

*Naxoshalle, Frankfurt*

![peak05](docs/images/peak05.jpg)
![mof01](docs/images/mof01.jpg)
![mof02](docs/images/mof02.jpg)
![peak01](docs/images/peak01.jpg)

---

## Enclosure

3D-printable housing for Arduino + sensor units:

| Part | File |
|------|------|
| Lid (Deckel) | [deckel.STL](arduino/housing/deckel.STL) |
| Base (Unterschale) | [unterschale.STL](arduino/housing/unterschale.STL) |
| Sensor housing — lid | [Sensorhuelle_Deckel.stl](arduino/housing/Sensorhuelle_Deckel.stl) |
| Sensor housing — base | [Sensorhuelle_unterteil.stl](arduino/housing/Sensorhuelle_unterteil.stl) |

*On GitHub, clicking an STL link opens an interactive 3D viewer — you can rotate and zoom.*

---

**Arduino:** Power over Ethernet, UDP to vvvv. Requires Adafruit 9DOF libraries (LSM303, L3GD20) and Arduino Ethernet. IP config: 192.168.1.x range, subnet 255.255.255.0.
