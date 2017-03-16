import controlP5.*;
import oscP5.*;
import netP5.*;
import processing.serial.*; 

import java.util.LinkedList;
import java.util.regex.Matcher;
import java.util.regex.Pattern; 

final boolean DEBUG = false; // osc
final boolean DEBUG_SERIAL = false;

// BPM Control
int curBoxPulse = 0;
int numberBoxes = 4;
boolean pulseRight = false;
boolean pulseLeft = false;

boolean useBPM = false;
boolean lastUseBPM = false;
int curBPM = 100;
int curBPMInterval = 0;
int lastBPMTime = 0;
int curPreset = 0;
int curPulsePreset = 0;
int curCyclePreset = 0;
public Slider bpmSlider;

class BPMType {

  public int BPM;
  public String name;
};

ArrayList bpmList = new ArrayList();

void parseBPM(String bpmLine)
{
  String[] data = split(bpmLine, ",");

  if(data.length == 2)
  {
    BPMType newBPM = new BPMType();
    newBPM.name = data[0];
    newBPM.BPM = Integer.parseInt(data[1]);

    bpmList.add(newBPM);
    BPMGraphicsList.addItem(data[0], bpmList.size()-1);
  }
}

void loadBPMs() {


  BPMGraphicsList = controlP5.addListBox("BPM List")
                        .setPosition(PADDING+900, PADDING*2 + 70)
                        .setSize(LIGHT_GROUP_WIDTH, 600)
                        .setItemHeight(20)
                        .actAsPulldownMenu(false)
                        .moveTo("presets");

  bpmList.clear();

  BufferedReader reader = createReader("bpms.txt");

  String line = null;

  do { 
    
    try {
      line = reader.readLine();
    } catch (IOException e) {
      e.printStackTrace();
      line = null;
    }

    if (line != null) {
      parseBPM(line);
    }

  } while (line != null);

  synchronizeBPMs();
}

void setBPMFromOSC(int i)
{
  if(i > bpmList.size())
    return;

  BPMType myBPM = (BPMType)bpmList.get(i);
  curBPM = myBPM.BPM;
  bpmSlider.setValue(curBPM);
}

void synchronizeBPMs() {

  String[] s = new String[bpmList.size()];
  for (int i = 0; i < s.length; i++) {
    BPMType myBPM = (BPMType)bpmList.get(i);
    s[i] = myBPM.name;
  }

  OscMessage message = new OscMessage("/BPMs/setLabels");
  message.add(s);
  oscP5.send(message, myRemoteLocation);

}

void CalculateInterval()
{
  double intermediateValue = (60.0/curBPM)*1000;
  curBPMInterval = (int)intermediateValue;
}

void TriggerOnBeat()
{
  BPMIndicateTog.setValue(useBPM);
  PRightIndicateTog.setValue(pulseRight);
  PLeftIndicateTog.setValue(pulseLeft);
  BPMIndicateTogPresets.setValue(useBPM);
  PRightIndicateTogPresets.setValue(pulseRight);
  PLeftIndicateTogPresets.setValue(pulseLeft);
  
  if(useBPM)
  {
     CalculateInterval();
     
     if(lastUseBPM != useBPM)
     {
       lastBPMTime = millis() - curBPMInterval-1;  
     }
     
     int curMillis = millis();
     if(curMillis - lastBPMTime > curBPMInterval)
     {
        lastBPMTime = curMillis - (curMillis - lastBPMTime - curBPMInterval);
        //applyPreset(curPreset);
        
        // PRESET 34 IS MY PULSE
        if(pulseRight)
        {
          curBoxPulse++;
          if(curBoxPulse >= numberBoxes)
          {
             curBoxPulse = 0; 
          }
          
          // Light Here
          applyPreset(curCyclePreset + curBoxPulse); 
        }
        else if(pulseLeft)
        {
          curBoxPulse--;
          if(curBoxPulse < 0)
          {
            curBoxPulse = numberBoxes-1;
          }
          
          // Light Here
          applyPreset(curCyclePreset + curBoxPulse); 
        }
        else
        {
          applyPreset(curPulsePreset);  
        }
     } 
  }
  else if(lastUseBPM != useBPM)
  {
     applyPreset(curPreset); 
  }
  
  lastUseBPM = useBPM;
}

void AddBPMControl()
{
 //controlP5.addToggle("useBPM").setPosition(120, 700);
 
 bpmSlider = controlP5.addSlider("curBPM")
             .setPosition(260, 700)
             .setRange(0, 300)
             .setSize(220, 20)
             .setLabel("BPM")
             .moveTo("presets");
}

// Special Push Buttons
public Bang PulseToBeatBang;
public Bang MoveAcrossLeftBang;
public Bang MoveAcrossRightBang;
public Bang PulseToBeatBangPresets;
public Bang MoveAcrossLeftBangPresets;
public Bang MoveAcrossRightBangPresets;

Toggle BPMIndicateTog;
Toggle PRightIndicateTog;
Toggle PLeftIndicateTog;
Toggle BPMIndicateTogPresets;
Toggle PRightIndicateTogPresets;
Toggle PLeftIndicateTogPresets;


void AddBPMBasedControlsToPresetList()
{                   
   PulseToBeatBangPresets = controlP5.addBang("Beat Pulse")
             .setPosition(20, 700)
             .setSize(60, 20)
             .setTriggerEvent(Bang.RELEASE)
             .setLabel("Pulse To Beat")
             .moveTo("presets");
            
  MoveAcrossLeftBangPresets = controlP5.addBang("Move Left")
             .setPosition(100, 700)
             .setSize(60, 20)
             .setTriggerEvent(Bang.RELEASE)
             .setLabel("Move Left")
             .moveTo("presets");
             
  MoveAcrossRightBangPresets = controlP5.addBang("Move Right")
             .setPosition(180, 700)
             .setSize(60, 20)
             .setTriggerEvent(Bang.RELEASE)
             .setLabel("Move Right")
             .moveTo("presets");
             
   BPMIndicateTogPresets = controlP5.addToggle("Use BPM").setPosition(20, 750).moveTo("presets");
   PRightIndicateTogPresets = controlP5.addToggle("Pulse RIGHT").setPosition(180, 750).moveTo("presets");
   PLeftIndicateTogPresets = controlP5.addToggle("PULSE LEFT").setPosition(100, 750).moveTo("presets");
}

void AddBangsToGUI()
{
  PulseToBeatBang = controlP5.addBang("doPulseToBeat")
             .setPosition(20, 700)
             .setSize(60, 20)
             .setTriggerEvent(Bang.RELEASE)
             .setLabel("Pulse To Beat");
            
  MoveAcrossLeftBang = controlP5.addBang("MoveAcrossLeft")
             .setPosition(100, 700)
             .setSize(60, 20)
             .setTriggerEvent(Bang.RELEASE)
             .setLabel("Move Left");
             
  MoveAcrossRightBang = controlP5.addBang("MoveAcrossRight")
             .setPosition(180, 700)
             .setSize(60, 20)
             .setTriggerEvent(Bang.RELEASE)
             .setLabel("Move Right");
             
   BPMIndicateTog = controlP5.addToggle("useBPM").setPosition(20, 750);
   PRightIndicateTog = controlP5.addToggle("pulseRight").setPosition(180, 750);
   PLeftIndicateTog = controlP5.addToggle("pulseLeft").setPosition(100, 750);
             
   AddBPMControl();
   AddBPMBasedControlsToPresetList();
}

void CheckBangs(ControlEvent theEvent) 
{ 
  if(theEvent.isFrom(PulseToBeatBang) || theEvent.isFrom(PulseToBeatBangPresets))
  {
     if( (useBPM && pulseLeft) || (useBPM && pulseRight))
     {
       useBPM = true;
       pulseRight = false;
       pulseLeft = false;  
     }
     else if(useBPM)
     {
        useBPM = false; 
     }
     else
     {
        useBPM = true; 
     }
     
  }
  else if(theEvent.isFrom(MoveAcrossLeftBang) || theEvent.isFrom(MoveAcrossLeftBangPresets))
  {
    println("Move Left");
    if(pulseLeft)
    {
       useBPM = false;
       pulseLeft = false;
       pulseRight = false; 
    }
    else
    {
       useBPM = true;
       pulseLeft = true;
       pulseRight = false; 
    }
    curBoxPulse = numberBoxes-1;
  }
  else if(theEvent.isFrom(MoveAcrossRightBang) || theEvent.isFrom(MoveAcrossRightBangPresets))
  {
    println("Move Right");
    if(pulseRight)
    {
       useBPM = false;
       pulseLeft = false;
       pulseRight = false; 
    }
    else
    {
       useBPM = true;
       pulseLeft = false;
       pulseRight = true; 
    }
    curBoxPulse = 0;
  }
  
}

final String PRESET_FILE = "presets.txt";

//final String RF_SERIAL_PORT = "/dev/tty.usbmodem1411";
final String RF_SERIAL_PORT = "/dev/tty.sddd";
//final String SERIAL_PORT = "/dev/tty.usbserial-A703X5EU";

final String SERIAL_PORT = "/dev/tty.usbserial-A100S23I";
//final String SERIAL_PORT = "/dev/cu.usbmodem1411";

final int INITIAL_PATTERN = 17;

//String IPAD_ADDRESS = "192.168.3.3";

String IPAD_ADDRESS = "192.168.1.87";

int IPAD_PORT = 8000;
int MY_PORT = 12001;

final int BAUD_RATE = 9600;
final int MESSAGE_SIZE = 14;
final int TIMING_ADDR = 129;
final int OFF_PATTERN = 0;
final int DELIMETER = (int)'z';
final int INTERVAL = 20;

int lastHeartbeat;

boolean stealth = false;

boolean rfPortActive = false;

ArrayList lightGroups = new ArrayList();
ArrayList presets = new ArrayList();

LightGroup groupAll;
// LightGroup groupHorizontalPoles;
// LightGroup groupVerticalPoles;
LightGroup groupBoxes;
// LightGroup groupDMX;
LightGroup groupPoles;
LightGroup groupBox3;
LightGroup groupBox4;

// ControlP5

final int LIGHT_GROUP_WIDTH = 270;
final int RADIO_SIZE = 20;
final int PADDING = 15;

ControlP5 controlP5;

String[] patterns = new String[127];
String[] mappings = new String[16];

ListBox presetList;
ListBox presetToPulse;
ListBox presetToCycle;
Textfield presetNamer;

ListBox BPMGraphicsList;

Toggle rfPortActiveToggle;

boolean sympathizeEvents = false;

Serial port;
Serial rf_port;
LinkedList messageQueue = new LinkedList();

// OSCP5

OscP5 oscP5;
NetAddress myRemoteLocation;
NetAddress myCompLocation;


// Map of which groups to address.
// In order of the lightGroups array.
// Object cuz oscP5.
// Object[] activeAddr = { 1.0, 0.0, 0.0, 0.0, 0.0 };
Object[] activeAddr = { 1.0, 0.0, 0.0 };

int[] patternsToIndeces;

void setup() {
  
  Matcher m = Pattern.compile("/preset/(\\d+)").matcher("/preset/23");

  m.find();
  println(m.group(1));



  size(1350, 800);

  patterns[17] = "pulseOnce";
  patterns[16] = "colorWipeMeterGradient";
  patterns[15] = "colorWipeMeter";
  patterns[14] = "colorChase";
  patterns[13] = "stripe";
  patterns[12] = "colorAlternator";
  patterns[11] = "colorWipe";
  patterns[10] = "bounce";
  patterns[9] = "pulseSaw";
  patterns[8] = "pulseSine";
  patterns[7] = "gradient";
  patterns[6] = "solidColor";
  patterns[OFF_PATTERN] = "off";
  patterns[5] = "rainbow";
  patterns[4] = "rainbowCycle";
  patterns[3] = "totesRandom";
  patterns[2] = "flickerStrobeFour";
  patterns[1] = "flickerStrobeTwo";

  mappings[0] = "snake";
  mappings[1] = "peak";
  mappings[2] = "valley";
  mappings[3] = "dither";
  mappings[4] = "dekonstruktor";
  mappings[5] = "horizontal";
  mappings[6] = "horiz-peak";
  mappings[7] = "horiz-valley";
  mappings[8] = "horiz-dither";
  mappings[9] = "horiz-dekonstruktor";
  mappings[10] = "vertical";
  mappings[11] = "vert-peak";
  mappings[12] = "vert-valley";
  mappings[13] = "vert-dither";
  mappings[14] = "vert-dekonstruktor";

  controlP5 = new ControlP5(this);

  // Only instantiate port if we know for sure it exists.
  // Port won't be null if you give it a bunk address.
  String[] serialPorts = Serial.list();
  println (serialPorts);
  for (int i = 0; i < serialPorts.length; i++) {
    if (serialPorts[i].equals(SERIAL_PORT)) {
      port = new Serial(this, SERIAL_PORT, BAUD_RATE);  
    }
     if (serialPorts[i].equals(RF_SERIAL_PORT)) {
      rf_port = new Serial(this, RF_SERIAL_PORT, BAUD_RATE);  
    }
  }
  if (port != null) {
    println("Using serial port " + SERIAL_PORT);
  } else { 
    println("Did not find an FTDI serial port!");
  }
    if (rf_port != null) {
    println("Using serial port " + RF_SERIAL_PORT);
  } else { 
    println("Did not find an RF serial port!");
  }

  // Think of this as push/pop/sympathizeEvents
  // first run of controlEvent causes probs when not all 
  // controllers have been created.
  sympathizeEvents = true;

  groupAll = new LightGroup("All", 0) ;
  // groupHorizontalPoles = new LightGroup("Horizontal Poles", 0);
  // groupVerticalPoles = new LightGroup("Vertical Poles", 7);
  groupPoles = new LightGroup("Box1", 1);
  groupBoxes = new LightGroup("Box2", 2);
  groupBox3 = new LightGroup("Box3", 3);
  groupBox4 = new LightGroup("Box4", 4);

  sympathizeEvents = false;



  int x = lightGroups.size() * LIGHT_GROUP_WIDTH + PADDING;
  
  presetNamer = controlP5.addTextfield("preset-namer")
                         .setPosition(PADDING, PADDING*2)
                         .setLabel("Save preset.")
                         .setSize(LIGHT_GROUP_WIDTH, 20)
                         .moveTo("presets");

  presetList = controlP5.addListBox("preset-list")
                        .setPosition(PADDING, PADDING*2 + 70)
                        .setSize(LIGHT_GROUP_WIDTH, 600)
                        .setItemHeight(20)
                        .actAsPulldownMenu(false)
                        .moveTo("presets");
                     
   presetToPulse = controlP5.addListBox("preset-to-pulse")
                        .setPosition(PADDING+300, PADDING*2 + 70)
                        .setSize(LIGHT_GROUP_WIDTH, 600)
                        .setItemHeight(20)
                        .actAsPulldownMenu(false)
                        .moveTo("presets");
                        
  presetToCycle = controlP5.addListBox("preset-to-cycle")
                        .setPosition(PADDING+600, PADDING*2 + 70)
                        .setSize(LIGHT_GROUP_WIDTH, 600)
                        .setItemHeight(20)
                        .actAsPulldownMenu(false)
                        .moveTo("presets");

  oscP5 = new OscP5(this, MY_PORT);
  myRemoteLocation = new NetAddress(IPAD_ADDRESS, IPAD_PORT);
  myCompLocation = new NetAddress(oscP5.ip(), MY_PORT);
//
  controlP5.addToggle("rfPortActive")
           .setPosition(120, 0);

  loadPresets();
    loadBPMs();
  synchronizePatterns();
  synchronizeMappings();

  AddBangsToGUI();
  //AddBPMControl();
  CalculateInterval();

}

void draw() {
  IntervalSend();
// if(DEBUG){
//  if(frameCount%2 == 0){
//  background(0);
// }
// else{
// background(40);
// }
// }
// else{
  background(0); 
// }
  if (port != null) heartbeat();

  // checks for the existence of port itself
  // still debugs if port isn't there
  if (!stealth) emptyMessageQueue();
  
  TriggerOnBeat();
}

void sendAllMessages() {
  for (int i = 0; i < lightGroups.size(); i++) {
    LightGroup l = (LightGroup)lightGroups.get(i);
    l.sendMessage();
  }
}

void emptyMessageQueue() {

  if (DEBUG_SERIAL && messageQueue.peek() != null) println("----------------");
    
  while (messageQueue.peek() != null) {
    byte b = ((Byte)messageQueue.poll()).byteValue();
    
    if (port != null) port.write(b);
    
    if (rfPortActive && rf_port != null) {
      rf_port.write(b);
    }
    
    if (DEBUG_SERIAL) println("[SERIAL] " + b);
  }

}

void heartbeat() {
  int now = millis();
  if (now - lastHeartbeat >= INTERVAL) {
    port.write(TIMING_ADDR);
    port.write(new Integer(now).toString());
    port.write(DELIMETER);
    
    if (rfPortActive && rf_port != null) {
      rf_port.write(TIMING_ADDR);
      rf_port.write(new Integer(now).toString());
      rf_port.write(DELIMETER);
    }
    
    lastHeartbeat = now;
  }
}

void keyPressed() {
  if (key == ' ')
    ((LightGroup)lightGroups.get(1)).sendMessage();
    ((LightGroup)lightGroups.get(2)).sendMessage();
}



void controlEvent(ControlEvent theEvent) {
  
  CheckBangs(theEvent);

  LightGroup l = checkLightControllers(theEvent);

  //if (keyPressed || l == groupAll) expressSympathy(theEvent);

  if (theEvent.isFrom(presetNamer)) {
    savePreset(theEvent.getStringValue());
    return;
  }

  if (theEvent.isFrom(presetList)) {
    useBPM = false;
    pulseRight = false;
    pulseLeft = false;
    curPreset = (int)theEvent.value();
    applyPreset(curPreset);
  }
  
  if (theEvent.isFrom(presetToPulse)){
     curPulsePreset = (int)theEvent.value(); 
  }
  
  if(theEvent.isFrom(presetToCycle))
  {
     curCyclePreset = (int)theEvent.value(); 
     if(curCyclePreset + numberBoxes > presets.size())
     {
        curCyclePreset = presets.size() - numberBoxes; 
     }
  }

  if(theEvent.isFrom(BPMGraphicsList))
  {
    BPMType theBPM = (BPMType)bpmList.get((int)theEvent.value());
    curBPM = theBPM.BPM;
    bpmSlider.setValue(curBPM);
  }

}

/**
 * Returns Light group controller came from or null if none.
 */
LightGroup checkLightControllers(ControlEvent theEvent) {
  
  for (Object o : lightGroups) {

    LightGroup l = (LightGroup)o;

    // h8 u cp5
    // Would have liked to do all listeners, but I couldn't, because there
    // are controller groups. Just did it all here to be consistent.

    if (theEvent.isFrom(l.bang)) {
      l.sendMessage();
      return l;
    }

    if (theEvent.isFrom(l.rateSlider)) {
      l.rate = (int)theEvent.value();
      return l;
    }

    if (theEvent.isFrom(l.brightnessSlider)) {
      l.brightness = (int)theEvent.value();
      return l;
    }

    if (theEvent.isFrom(l.patternList)) {
      l.pattern = (int)theEvent.value();
      return l;
    }

    if (theEvent.isFrom(l.mappingList)) {
      l.mapping = (int)theEvent.value();
      return l;
    }

    if (theEvent.isFrom(l.colorPicker1)) {
      l.color1 = (color)theEvent.value();
      return l;
    }

    if (theEvent.isFrom(l.colorPicker2)) {
      l.color2 = (color)theEvent.value();
      return l;
    }

  }

  return null;

}


void expressSympathy(ControlEvent theEvent) {

  if (!sympathizeEvents) {
    
    sympathizeEvents = true;

    String name = theEvent.name();
    name = name.substring(0, name.indexOf("-"));

    for (Object o : lightGroups) {

      LightGroup l = (LightGroup)o;
      String addr = name + "-" + l.address;
      Controller c = controlP5.getController(addr);
      
      // Controller groups are weird.
      if (theEvent.isGroup() && theEvent.getGroup() instanceof ColorPicker) {
        
        if (name.equals("picker1")) {
          l.setColor1((int)theEvent.value());
        } else if (name.equals("picker2")) {
          l.setColor2((int)theEvent.value());
        }

      } else if (theEvent.isGroup() && theEvent.getGroup() instanceof RadioButton) {

        if (name.equals("patterns")) {
          l.setPattern((int)theEvent.value());
        } else if (name.equals("mappings")) { 
          l.setMapping((int)theEvent.value());
        }

      } else if (c != null) {

        c.setValue(theEvent.value());

      }


    }

    sympathizeEvents = false;

  }

}

void applyPreset(int presetIndex) {

  LightGroupSettings[] preset = (LightGroupSettings[])presets.get(presetIndex);
  
  for (int i = 0; i < lightGroups.size(); i++) {
    LightGroup l = (LightGroup)lightGroups.get(i);
    l.applySettings(preset[i]);
  }


  sendAllMessages();

}

void savePreset(String presetName) {

  LightGroupSettings[] preset = new LightGroupSettings[lightGroups.size()];

  for (int i = 0; i < lightGroups.size(); i++) {
    LightGroup l = (LightGroup)lightGroups.get(i);
    preset[i] = l.getSettings();
  }

  presets.add(preset);
  presetList.addItem(presetName, presets.size()-1);
  presetToPulse.addItem(presetName, presets.size()-1);
  presetToCycle.addItem(presetName, presets.size() - 1);

  writePresets();

}



void writePresets() {

  PrintWriter output = createWriter(PRESET_FILE);

  for (int i = 0; i < presets.size(); i++) {

    LightGroupSettings[] l = (LightGroupSettings[])presets.get(i);
    String[] serialized = new String[l.length];

    String name = presetList.getItem(i).getName();

    for (int j = 0; j < serialized.length; j++) {
      serialized[j] = l[j].serialize();
    }

    output.println(name + ":" + join(serialized, ":"));

  }

  output.flush();
  output.close();

  synchronizePresets();

}

void loadPresets() {

  BufferedReader reader = createReader(PRESET_FILE);

  String line = null;

  do { 
    
    try {
      line = reader.readLine();
    } catch (IOException e) {
      e.printStackTrace();
      line = null;
    }

    if (line != null) {
      parsePreset(line);
    }

  } while (line != null);

  synchronizePresets();

}




void synchronizePresets() {

  String[] s = new String[presets.size()];
  for (int i = 0; i < s.length; i++) {
    s[i] = presetList.getItem(i).getName();
  }

  OscMessage message = new OscMessage("/Presets/setLabels");
  message.add(s);
  oscP5.send(message, myRemoteLocation);

}

void synchronizePatterns() {

  // count non-null presets
  int numPatterns = 0;
  for (int i = 0; i < patterns.length; i++) {
    if (patterns[i] != null) {
      numPatterns++;
    }
  }

  patternsToIndeces = new int[numPatterns];

  // make arr
  String[] s = new String[numPatterns];
  int j = 0;
  for (int i = 0; i < patterns.length; i++) {
    if (patterns[i] != null) {
      s[j] = patterns[i];
      patternsToIndeces[j] = i;
      j++;
    }
  }

  OscMessage message = new OscMessage("/Patterns/setLabels");
  message.add(s);
  oscP5.send(message, myRemoteLocation);

}

void synchronizeMappings() {

  // count non-null presets
  int numMappings = 0;
  for (int i = 0; i < mappings.length; i++) {
    if (mappings[i] != null) {
      numMappings++;
    }
  }

  // make arr
  String[] s = new String[numMappings];
  int j = 0;
  for (int i = 0; i < mappings.length; i++) {
    if (mappings[i] != null) {
      s[j] = mappings[i];
      j++;
    }
  }

  OscMessage message = new OscMessage("/Mappings/setLabels");
  message.add(s);
  oscP5.send(message, myRemoteLocation);

}

void parsePreset(String s) {
  
  String[] data = split(s, ":");

  LightGroupSettings[] preset = new LightGroupSettings[data.length-1];

  for (int i = 0; i < preset.length; i++) {
    preset[i] = new LightGroupSettings(data[i+1]);
  }

  presets.add(preset);
  presetList.addItem(data[0], presets.size()-1);
  presetToPulse.addItem(data[0], presets.size()-1);
  presetToCycle.addItem(data[0], presets.size() - 1);
}

void IntervalSend()
{
    for (int i = 0; i < lightGroups.size(); i++) {
      LightGroup l = (LightGroup)lightGroups.get(i);
      if(l.isFromOSC)
      {
        l.isFromOSC = false;
        l.sendMessage();
      }
    }
}
