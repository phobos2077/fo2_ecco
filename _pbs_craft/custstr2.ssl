#define var variable

#define charv(x,y)  else if ostr>=str+x and ostr<str+y then return x
#define charv_(x,y) if ostr>=str+x and ostr<str+y then return x
#define cmp(x)      if ostr<str+x then begin

/*procedure get_char(var ostr, var str) begin

    if ostr==str then return "";
    
    if ostr<str+"A" then begin
    
    if ostr>=str+" " and ostr<str+"!" then return " ";
        charv("!","\"");
        charv("\"","#");
        charv("#","$");
        charv("$","%");
        charv("%","&");
        charv("&","'");
        charv("'","(");
        charv("(",")");
        charv(")","*");
        charv("*","+");
        charv("+",",");
        charv(",","-");
        charv("-",".");
        charv(".","/");
        charv("/","0");
        charv("0","1");
        charv("1","2");
        charv("2","3");
        charv("3","4");
        charv("4","5");
        charv("5","6");
        charv("6","7");
        charv("7","8");
        charv("8","9");
        charv("9",":");
        charv(":",";");
        charv(";","<");
        charv("<","=");
        charv("=",">");
        charv(">","?");
        charv("?","@");
        charv("@","A");
    end else if ostr<str+"a" then begin
        if ostr>=str+"A" and ostr<str+"B" then return "A";
        charv("B","C");
        charv("C","D");
        charv("D","E");
        charv("E","F");
        charv("F","G");
        charv("G","H");
        charv("H","I");
        charv("I","J");
        charv("J","K");
        charv("K","L");
        charv("L","M");
        charv("M","N");
        charv("N","O");
        charv("O","P");
        charv("P","Q");
        charv("Q","R");
        charv("R","S");
        charv("S","T");
        charv("T","U");
        charv("U","V");
        charv("V","W");
        charv("W","X");
        charv("X","Y");
        charv("Y","Z");
        charv("Z","[");
        charv("[","\\");
        charv("\\","]");
        charv("]","^");
        charv("^","_");
        charv("_","`");
        charv("`","a");
    end else begin
        if ostr>=str+"a" and ostr<str+"b" then return "a";
        charv("b","c");
        charv("c","d");
        charv("d","e");
        charv("e","f");
        charv("f","g");
        charv("g","h");
        charv("h","i");
        charv("i","j");
        charv("j","k");
        charv("k","l");
        charv("l","m");
        charv("m","n");
        charv("n","o");
        charv("o","p");
        charv("p","q");
        charv("q","r");
        charv("r","s");
        charv("s","t");
        charv("t","u");
        charv("u","v");
        charv("v","w");
        charv("w","x");
        charv("x","y");
        charv("y","z");
        charv("z","{");
        charv("{","|");
        charv("|","}");
        charv("}","~");
    end
//    return "Z";
    return "";
end*/

procedure get_char(var ostr, var str) begin
    if ostr==str then return "";

    cmp("A")
        cmp("1")
            cmp(")")
                cmp("%")
                    cmp("#")
                        charv_(" ","!");
                        charv("!","\"");
                        charv("\"","#");
                    end else begin
                        charv_("#","$");
                        charv("$","%");
                    end
                end else begin  
                    charv_("%","&");
                    charv("&","'");
                    charv("'","(");
                    charv("(",")");
                end
            end else cmp("-")
                charv_(")","*");
                charv("*","+");
                charv("+",",");
                charv(",","-");
            end else begin
                charv_("-",".");
                charv(".","/");
                charv("/","0");
                charv("0","1");
            end
        end else cmp("9")
            cmp("5")
                cmp("3")
                    charv_("1","2");
                    charv("2","3");
                end else begin
                    charv_("3","4");
                    charv("4","5");
                end
            end else cmp("7")
                charv_("5","6");
                charv("6","7");
            end else begin
                charv_("7","8");
                charv("8","9");
            end
        end else cmp("=")
            cmp(";")
                charv_("9",":");
                charv(":",";");
            end else begin
                charv_(";","<");
                charv("<","=");
            end
        end else cmp("?")
            charv_("=",">");
            charv(">","?");
        end else begin
            charv_("?","@");
            charv("@","A");
        end
    end else cmp("a")
        cmp("Q")
            cmp("I")
                cmp("E")
                    cmp("C")
                        charv_("A","B");
                        charv("B","C");
                    end else begin
                        charv_("C","D");
                        charv("D","E");
                    end
                end else cmp("G")
                    charv_("E","F");
                    charv("F","G");
                end else begin
                    charv_("G","H");
                    charv("H","I");
                end
            end else cmp("M")
                cmp("K")
                    charv_("I","J");
                    charv("J","K");
                end else begin
                    charv_("K","L");
                    charv("L","M");
                end
            end else cmp("O")
                charv_("M","N");
                charv("N","O");
            end else begin
                charv_("O","P");
                charv("P","Q");
            end
        end else cmp("Y")
            cmp("U")
                cmp("S")
                    charv_("Q","R");
                    charv("R","S");
                end else begin
                    charv_("S","T");
                    charv("T","U");
                end
            end else cmp("W")
                charv_("U","V");
                charv("V","W");
            end else begin
                charv_("W","X");
                charv("X","Y");
            end
        end else cmp("]")
            cmp("[")
                charv_("Y","Z");
                charv("Z","[");
            end else begin
                charv_("[","\\");
                charv("\\","]");
            end
        end else cmp("_")
            charv_("]","^");
            charv("^","_");
        end else begin
            charv_("_","`");
            charv("`","a");
        end
    end else cmp("q")
        cmp("i")
            cmp("e")
                cmp("c")
                    charv_("a","b");
                    charv("b","c");
                end else begin
                    charv_("c","d");
                    charv("d","e");
                end
            end else cmp("g")
                charv_("e","f");
                charv("f","g");
            end else begin
                charv_("g","h");
                charv("h","i");
            end
        end else cmp("m")
            cmp("k")
                charv_("i","j");
                charv("j","k");
            end else begin
                charv_("k","l");
                charv("l","m");
            end
        end else cmp("o")
            charv_("m","n");
            charv("n","o");
        end else begin
            charv_("o","p");
            charv("p","q");
        end 
    end else cmp("y")
        cmp("u")
            cmp("s")
                charv_("q","r");
                charv("r","s");
            end else begin
                charv_("s","t");
                charv("t","u");
            end
        end else cmp("w")
            charv_("u","v");
            charv("v","w");
        end else begin
            charv_("w","x");
            charv("x","y");
        end
    end else cmp("{")
        charv_("y","z");
        charv("z","{");
    end else begin
        charv_("{","|");
        charv("|","}");
        charv("}","~");
    end
    return "";
end


procedure wordar(var word, var cell) begin
    var rstr:=""; var str:=""; var c_cell; /*var j;*/ var tmp; /*var end_flag;*/

    while c_cell<cell do begin
        tmp:=get_char(word,str);
        if tmp=="" then return "";
        else begin
            if tmp=="|" then c_cell+=1;
            str+=tmp;
        end
    end

    while 1 do begin
        tmp:=get_char(word,str);
        if tmp=="" or tmp=="|" then return rstr;
        else begin
            rstr+=tmp;
            str+=tmp;
        end
    end
    
/*    while c_cell<=cell and j<256 and not(end_flag) do begin
        tmp:=get_char(word,str);
        if tmp=="" then end_flag := 1;
        else begin
            str+=tmp;
            if tmp!="|" then rstr+=tmp;
            if tmp=="|" or word==str then begin
                if c_cell==cell then return rstr;
                c_cell+=1;
                rstr:="";
            end
            j+=1;
        end
    end*/

    return "";
end

/*procedure cust_str(var ostr, var word, var rnum) begin
    var str:=""; var i; var tmp; var rstr:=""; var j;
    while ostr!=str and i<256 do begin
        tmp:=get_char(ostr,str);
        if tmp=="#" then begin
            str+="###";
            tmp:=wordar(word,random(j,j+rnum-1));
            rstr+=tmp;
            j+=rnum;
        end else begin
            str+=tmp;
            rstr+=tmp;
        end
        i+=1;
    end
    return rstr;
end*/