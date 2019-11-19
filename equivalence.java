public float position(float pos){
    //Being:
    //MAX_Y and MIN_Y, S and N
    //MAX_X and MIN_Y, E and W
    //CENTER_X and CENTER_Y, point zero
    //defined as global
    if(between(pos,MAX_Y,CENTER_Y)) return equivalentScale(pos,MAX_Y,CENTER_Y,"N");
    if(between(pos,MAX_X,CENTER_X)) return equivalentScale(pos,MAX_X,CENTER_X,"E");
    if(between(pos,MIN_Y,CENTER_Y)) return equivalentScale(pos,MIN_Y,CENTER_Y,"S");
    if(between(pos,MIN_X,CENTER_X)) return equivalentScale(pos,MIN_X,CENTER_X,"W");
    else return 0;
}

public boolean between(float val, float val_1, float val_2){
    if(val_1 > val_2) return (val<val_1 && val>val_2);
    if(val_2 > val_1) return (val>val_1 && val<val_2);
    else return false;
}

public float equivalentScale(float val, float val_1, float val_2, String orientation){
    float proportion;
    float final_pos;
    proportion = abs(val_2)/abs(val_1);
    final_pos = final_pos + 127 * proportion;
    switch(orientation){
        case "N":
            return final_pos;
        case "E":
            return final_pos;
        case "S":
            return -final_pos;
        case "W":
            return -final_pos;
    }
}