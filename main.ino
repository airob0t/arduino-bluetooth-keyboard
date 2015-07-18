String keys = ""; 
boolean n = 0 , s = 0; 

void setup() 
{ 
  Serial1.begin(9600); 
  Keyboard.begin(); 
} 

int check(String key)   //不知道c语言有啥好方法从输入中识别标识符，只好打表了。。 
{ 
if(keys.equalsIgnoreCase("LEFT_CTRL")) { s = 1; return(KEY_LEFT_CTRL); } 
      else if(keys.equalsIgnoreCase("LEFT_SHIFT")) { s = 1; return(KEY_LEFT_SHIFT); } 
      else if(keys.equalsIgnoreCase("LEFT_ALT")) { s = 1; return(KEY_LEFT_ALT); } 
      else if(keys.equalsIgnoreCase("LEFT_GUI")) { s = 1; return(KEY_LEFT_GUI); } 
      else if(keys.equalsIgnoreCase("RIGHT_CTRL")) { s = 1; return(KEY_RIGHT_CTRL); } 
      else if(keys.equalsIgnoreCase("RIGHT_SHIFT")) { s = 1; return(KEY_RIGHT_SHIFT); } 
      else if(keys.equalsIgnoreCase("RIGHT_ALT")) { s = 1; return(KEY_RIGHT_ALT); } 
      else if(keys.equalsIgnoreCase("RIGHT_GUI")) { s = 1; return(KEY_RIGHT_GUI); } 
      else if(keys.equalsIgnoreCase("UP_ARROW")) { s = 1; return(KEY_UP_ARROW); } 
      else if(keys.equalsIgnoreCase("DOWN_ARROW")) { s = 1; return(KEY_DOWN_ARROW); } 
      else if(keys.equalsIgnoreCase("LEFT_ARROW")) { s = 1; return(KEY_LEFT_ARROW); } 
      else if(keys.equalsIgnoreCase("RIGHT_ARROW")) { s = 1; return(KEY_RIGHT_ARROW); } 
      else if(keys.equalsIgnoreCase("BACKSPACE")) { s = 1; return(KEY_BACKSPACE); } 
      else if(keys.equalsIgnoreCase("TAB")) { s = 1; return(KEY_TAB); } 
      else if(keys.equalsIgnoreCase("RETURN")) { s = 1; return(KEY_RETURN); } 
      else if(keys.equalsIgnoreCase("ESC")) { s = 1; return(KEY_ESC); } 
      else if(keys.equalsIgnoreCase("INSERT")) { s = 1; return(KEY_INSERT); } 
      else if(keys.equalsIgnoreCase("DELETE")) { s = 1; return(KEY_DELETE); } 
      else if(keys.equalsIgnoreCase("PAGE_UP")) { s = 1; return(KEY_PAGE_UP); } 
      else if(keys.equalsIgnoreCase("PAGE_DOWN")) { s = 1; return(KEY_PAGE_DOWN); } 
      else if(keys.equalsIgnoreCase("HOME")) { s = 1; return(KEY_HOME); } 
      else if(keys.equalsIgnoreCase("END")) { s = 1; return(KEY_END); } 
      else if(keys.equalsIgnoreCase("CAPS_LOCK")) { s = 1; return(KEY_CAPS_LOCK); } 
      else if(keys.equalsIgnoreCase("F1")) { s = 1; return(KEY_F1); } 
      else if(keys.equalsIgnoreCase("F2")) { s = 1; return(KEY_F2); } 
      else if(keys.equalsIgnoreCase("F3")) { s = 1; return(KEY_F3); } 
      else if(keys.equalsIgnoreCase("F4")) { s = 1; return(KEY_F4); } 
      else if(keys.equalsIgnoreCase("F5")) { s = 1; return(KEY_F5); } 
      else if(keys.equalsIgnoreCase("F6")) { s = 1; return(KEY_F6); } 
      else if(keys.equalsIgnoreCase("F7")) { s = 1; return(KEY_F7); } 
      else if(keys.equalsIgnoreCase("F8")) { s = 1; return(KEY_F8); } 
      else if(keys.equalsIgnoreCase("F9")) { s = 1; return(KEY_F9); } 
      else if(keys.equalsIgnoreCase("F10")) { s = 1; return(KEY_F10); } 
      else if(keys.equalsIgnoreCase("F11")) { s = 1; return(KEY_F11); } 
      else if(keys.equalsIgnoreCase("F12")) { s = 1; return(KEY_F12); } 
      else if(keys.equalsIgnoreCase("^p")) { s = 0; return 500; }  //开启按模式 
      else if(keys.equalsIgnoreCase("^e")) { s = 0; return 501; } //结束按模式 
      else { s = 0;  return int(keys[0]); }//单按 
} 

void loop() 
{ 
  while (Serial1.available() > 0)  //有输入? 
    { 
        keys += char(Serial1.read()); 
        delay(3); 
    } 
  if (keys.length() > 0)//输入字节 > 0 ? 
    { 
     if(check(keys) == 500)//检测是否开启按模式 
       { 
         n = 1;   //标注已开启按模式 
         keys = "";   //字符串复位 
         Serial1.println("start the press mode!");  //提示手机开启模式了 
         while(n == 1) 
         { 
           while (Serial1.available() > 0)   
            { 
              keys += char(Serial1.read()); 
              delay(3); 
            } 
           if (keys.length() > 0) 
            { 
              if(check(keys) == 501)  //检测是否结束按模式 
              { n = 0; Serial1.println("end the mode!");} 
              else { 
                    Keyboard.press(check(keys)); 
                    Serial1.println("pressed"); 
                    } 
              keys = ""; 
            } 
          } 
       Keyboard.releaseAll();  //释放所有按键 
      } 
      else if(s == 1 ) Keyboard.write(check(keys));  //s标注是否是特殊按键,然后按下特殊按键 
      else Keyboard.print(keys);  //输出非特殊按键 
   } 
  keys = ""; 
}