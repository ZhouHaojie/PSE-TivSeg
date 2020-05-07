# PSE-TivSeg

[中文](https://github.com/ZhouHaojie/PSE-TivSeg/tree/master/README.md) | [German](https://github.com/ZhouHaojie/PSE-TivSeg/tree/master/README_DE.md)

## 实现目标

- 总体目标是使用TivSeg进行对象检测和跟踪
- TivSeg能够独立跟随前面的车辆（带有标记）
- 在初始状态下，首先应搜索标记
- 与识别标记的距离应保持恒定
- 应当识别并考虑路线中的障碍
- 状态和调试信息应连续输出并记录
- 在操作过程中应能够输入/更改配置参数和行程命令

## 要求

- 通过RealSense-camera获取用于标记和障碍物检测的图像和距离信息。图像评估的模块（“Region Growing”算法）用于物体识别。预处理和用于查询距离信息的接口在“Schnittstellenspezifikation (partiell) Input-Interface von der Kamera”给出。
- 如果没有识别出标记，我们应该通过一定的方法来找到它，例如通过简单的旋转搜索标记。
- 应该根据在图像评估中获得的信息来触发控制TivSeg的决策。我们创建一个基础结构，该基础结构允许不同的component来订阅，然后触发相应的动作发布-订阅模式）:
  - 标记搜索
  - 追踪模式
  - 避免障碍
- 在PID控制器的帮助下，与前方车辆的距离和转向角应保持恒定。用于电机控制的相应模块已给出，应将其集成。该模块的接口在“Schnittstellenspezifikation (partiell) Motor-Regler”给出
- 在第一步开发中，应使用具有相同接口的控制模块代替自动距离控制。这应该通过终端接收驱动命令（速度，转向）。
- 在操作过程中，应该能够通过终端输入配置参数和运行命令（请参见“Befehlsspezifikation Fahrbefehle und Konfiguration”）。更改的参数应直接影响正在运行的系统。
- 所有输入命令应通过脚本执行。脚本由下面定义的一系列命令组成。
- 系统的所有子组件的状态和调试信息应能够在控制台上输出并写入日志文件。应该输出全局时间戳，并且日志记录的详细程度应该是可调整的。已经指定了基本功能（“诊断”类）
- 在模块级别，所有组件均应可测试。为此，在开发过程中应连续使用单元测试。

## Schnittstellenspezifikation (partiell) Input-Interface von der Kamera

- `class SensorManager `

  - `bool runOnce();`

    > Soll periodisch aufgerufen werden um ein neues Bild zu holen und zu verarbeiten. Der Rückgabgewert gibt an, ob die Operation erfolgreich war.

  - `std::vector<MarkerInfo>& get_marker_list();`

    > Gibt eine Liste aus erkannten Markern im zuletzt verarbeiteten Bild zurück. Eine MarkerInfo enthält dabei eine BoundingBox für einen erkannten Marker sowie einen Wert [0; 100], welcher die Zuverlässigkeit der Erkennung wiedergibt. „100“ steht dabei für die höchste Zuverlässigkeit.

  - `double get_depth(int x, int y);`

    > Gibt die Tiefeninformation eines Pixels (x|y) im zuletzt verarbeiteten Bild in Metern zurück

## Schnittstellenspezifikation (partiell) Motor-Regler 

- `class DriveController`

  - `void updateController(int speed, int steering);`

    > Setzt neue Werte für die Geschwindigkeit und die Lenkung als Eingabe an den Regler. Liegt der letzte update() Aufruf mehr als 500ms zurück, schaltet der Regler die Motoren auf stopp (Sicherheitsabschaltung). Der Wertebereich beträgt jeweils +/100, wobei keine direkte Korrelation zwischen Wert und einer (Winkel)Geschwindigkeit vorliegt. -100 als steering-Wert bedeutet, dass das linke Rad stehenbleibt und das rechte Rad mit der vorgegebenen Geschwindigkeit dreht.

  - `void updateDirect(int speed, int steering);`

    > Setzt neue Werte für die Geschwindigkeit und die Lenkung ohne Regler für den Testbetrieb im aufgebockten Modus. Wird nur für die erste Testphase (statt update()) benötigt. Werte wie bei updateController

  - `void updateDirectMotor(int speedLeft, int speedRight);`

    > Setzt neue Werte für die Motoren ohne Regler für den Testbetrieb im aufgebockten Modus. Wird nur für die erste Testphase (statt updateController()) benötigt.

  - `void step();`

    > Diese Methode muss unabhängig von der restlichen Anwendung alle 10ms aufgerufen werden.

## Befehlsspezifikation Fahrbefehle und Konfiguration

- set -l \<value>

  > Setzt den Grad der Logging Informationen \<value>, welche von der Anwendung ausgegeben werden. 0 = Error, 1 = Warning, 2 = Info, 3 = Debug, 4 = Verbose

- set -t \<value>

  > Setzt die maximale Zeit \<value>, die der TivSeg ohne weitere Eingabe fahren darf. Nach dieser Zeit muss ein Nothalt erfolgen.

- set -d \<value> 

  > Setzt den angepeilten Abstand \<value> zum Marker der automatischen Steuerung. 

- drive \<time> \<velocity> \<steering>

  > Fahre eine Zeit \<time> [0 – max] mit Geschwindigkeit \<velocity> [-100; 100] und einer Lenkung \<steering> [-100; 100]. Die Lenkung hat einen default Wert von 0, was einer geraden Ausrichtung entspricht.

- script \<file>

  > Führe ein Skript aus \<file> aus. Das Skript soll alle vorgestellten Befehle enthalten können. Jeder Befehl blockiert bis er vollständig ausgeführt wurde.

- STRG + c

  > Bricht die aktuelle Befehlsausführung sofort ab und kehrt in das Terminal zurück. (Hinweis: Funktion signal() )

- search Sucht einen Marker in der Umgebung.

- mode \<mode> 

  > Setzt den Fahrmodus \<mode> [1:automatic; 2:manual]

## 实习任务

1. 将本规范中的要求转换为用例和顺序图
2. 从规范和图（类图）派生软件设计
3. Design-Review mit dem Betreuer
4. 软件和测试用例的实现
5. 进行组件测试（单元测试）（现场安装测试）
6. Implementierungs-review mit dem Betreuer
7. 进行集成测试（目标硬件处于顶升模式）
8. 进行验收测试（目标硬件处于自主模式）

## 提交项目

1. Enterprise Architect中的系统设计（用例，顺序图，类图）

2. 软件项目（通过KIT-Gitlab）
3. 随附文档（per Doxygen mit im Softwareprojek）