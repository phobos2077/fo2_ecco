procedure atoim(variable ostr, variable bstr) begin
    variable begin
        i;
        str;
        val;
    end
    str:=bstr;
    while (ostr!=str and ostr<=str+":" and ostr>=str+"0") do begin
        while not((ostr>str+i and ostr<str+(i+1)) or ostr==str+i) and i<9 do i+=1;
        str+=i; val:=val*10+i; i:=0;
    end
    return val;
end

#define atoi(x) atoim(x,"")
