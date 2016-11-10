import processing.video.*;

Capture cam;
PImage firstImage;

void setup() {
  size(640, 480);

  String[] cameras = Capture.list();
  
  if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } else {
    println("Available cameras:");
    for (int i = 0; i < cameras.length; i++) {
      println(cameras[i]);
    }
    
    // The camera can be initialized directly using an 
    // element from the array returned by list():
    cam = new Capture(this, cameras[0]);
    cam.start();     
  }      
  
  if (cam.available() == true) {
    cam.read();
  }
  firstImage = cam;
}

void draw() {
  if (cam.available() == true) {
    cam.read();
  }
  PImage img = cam;
  
  
  for (int x = 0; x < img.width; x++) {
    for (int y = 0; y < img.height; y++ ) {
    // Calculate the 1D pixel location
    int loc = x + y*img.width;
    int newPixel = img.pixels[loc] - firstImage.pixels[loc];
    // Get the R,G,B values from image
    //float r = red   (img.pixels[loc]);
    //float g = green (img.pixels[loc]);
    //float b = blue  (img.pixels[loc]);
    // Change brightness according to the mouse here
    //float adjustBrightness = ((float) mouseX / width) * 8.0;
    //r *= adjustBrightness;
    //g *= adjustBrightness;
    //b *= adjustBrightness;
    // Constrain RGB to between 0-255
    //r = constrain(r,0,255);
    //g = constrain(g,0,255);
    //b = constrain(b,0,255);
    // Make a new color and set pixel in the window
    //color c = color(r,g,b);
    img.pixels[loc] = newPixel;
    }
  }
  
  
  image(img, 0, 0);
  // The following does the same, and is faster when just drawing the image
  // without any additional resizing, transformations, or tint.
  //set(0, 0, cam);
}