#include <Keyboard.h>
#include <Wire.h>
#include <skywriter.h>

#define PIN_TRFR  12    // TRFR Pin of Skywriter
#define PIN_RESET 13    // Reset Pin of Skywriter

long touch_timeout = 0;
int air_wheel_counter = 0;

void setup() {
 
  Keyboard.begin();
  
  Skywriter.begin(PIN_TRFR, PIN_RESET);

  // Bind skywriter events
  Skywriter.onTouch(touch);
  Skywriter.onAirwheel(airwheel);
  Skywriter.onGesture(gesture);
}


void loop() {
  Skywriter.poll(); // Poll for any updates from Skywriter

  if( touch_timeout > 0 ) touch_timeout--; 
}

void enter(){
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
}

void gesture(unsigned char type){
  switch (type){
    /* Move current window to next display on right
     * Ctrl-Alt-P
     */
    case SW_FLICK_WEST_EAST:
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.print("p");
      Keyboard.releaseAll();
      break;
    
    /* Move current window to next display on left
     * Ctrl-Alt-O
     */
    case SW_FLICK_EAST_WEST:
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.print("o");
      Keyboard.releaseAll();
      break;

    /* Spread all windows
     * Super-W 
     */
    case SW_FLICK_SOUTH_NORTH:
      Keyboard.press(KEY_LEFT_GUI); 
      Keyboard.print("w");
      Keyboard.release(KEY_LEFT_GUI);
      break;
    
    /* Spread all windows of current application from across all workspaces 
     * Control-Shift-Super-W 
     */
    case SW_FLICK_NORTH_SOUTH:
      Keyboard.press(KEY_LEFT_GUI); 
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_LEFT_SHIFT); 
      Keyboard.print("w");
      Keyboard.releaseAll();
      break;
  }
}

void airwheel(int number){
  if( air_wheel_counter > 5 ){// Prevent the command being run excessive times for negligible difference
    if( number > 0 ){ // If the wheel's going in the "increase" direction
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.print("]"); // Increase colour temperature (using custom keyboard shortcut for redshift)
      Keyboard.release(KEY_LEFT_ALT);
    }
    else{
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.print("["); // Decrease colour temperature (using custom keyboard shortcut for redshift)
      Keyboard.release(KEY_LEFT_ALT);
    }
    
    air_wheel_counter = 0;
  }
  else{
    air_wheel_counter++;
  }
  touch_timeout = 10000;
}

void touch(unsigned char type){
  /*Serial.println("Got touch ");
  Serial.print(type,DEC);
  Serial.print('\n');*/

  if( touch_timeout > 0 ) return; //Ensure that falsely detected touches within a small time interval of a real touch are ignored
  
  switch (type) {

    /* A note regarding SW_TOUCH_CENTER
     * The center touch event is very sensitive for some reason, so triggers a lot.
     * Though it is theoretically possible to detect a center touch using the raw x,y,z values provided by the skywriter,
     * I have found them to be very buggy and inconsistent.
     */


    /* Launch terminal
     * Ctrl-Alt-T
     */
    case SW_TOUCH_WEST: 
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.print("t");
      Keyboard.releaseAll();
      break;

    /* Launch selective area screenshot
     * Alt-; is the keyboard shortcut I have it bound to
     */
    case SW_TOUCH_SOUTH:
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.print(";");
      Keyboard.release(KEY_LEFT_ALT);
      break;

    /* Launch spotify web player
     * Switch to chrome, open new tab, and start typing URL
     */
    case SW_TOUCH_NORTH:
      Keyboard.press(KEY_LEFT_GUI); 
      Keyboard.print("2"); // chrome always is second along my taskbar
      delay(5); // Allow time for browser to pop up
      Keyboard.release(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.print("t");
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.print("o"); // On my chrome, open.spotify.com is auto suggested after typing o
      enter();
      break;

    /* Launch facebook messenger
     * Switch to chrome, open new tab, and start typing URL
     */
    case SW_TOUCH_EAST:
      Keyboard.press(KEY_LEFT_GUI); 
      Keyboard.print("2"); // chrome always is second along my taskbar
      delay(5); // Allow time for browser to pop up
      Keyboard.release(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.print("t");
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.print("m"); // On my chrome, messenger.com is auto suggested after typing m
      enter();
      break;

  }

  touch_timeout = 10000;
}



