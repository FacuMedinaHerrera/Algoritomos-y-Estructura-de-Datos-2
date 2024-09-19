package aed;

public class InternetToolkit {
    public InternetToolkit() {
    }

    public Fragment[] tcpReorder(Fragment[] fragments) {
        // IMPLEMENTAR
        //isertion sort
        for(int i = 1 ; i< fragments.length;i++){
            Fragment elem = fragments[i];
            int j = i-1;
            while(j>= 0 && fragments[j].compareTo(elem)>0){
                fragments[j+1]=fragments[j];
                j--;
            }
            fragments[j+1]=elem;
    
        }

        return fragments;
    }

    public Router[] kTopRouters(Router[] routers, int k, int umbral) {
        // IMPLEMENTAR
        Router[]res=new Router[k];
        Router[] ordenados=mergeSort(routers);

        for(int i=0;i<ordenados.length;i++){
            if(ordenados[i].getTrafico()>umbral && i<k){
                res[i]=ordenados[i];
            }else{
                break;
            }
        }

        return res;
    }
    
    public IPv4Address[] sortIPv4(String[] ipv4) {
        // IMPLEMENTAR
        //primero copiamos el String[] a un int[][] eliminando los "." del medio y facilitando la comparacion.
        int[][]copia=new int[ipv4.length][4];
        for(int i=0;i<ipv4.length;i++){ //complejidad O(n*k) con k = la cadena de caracteres mas larga de los ip.
            copia[i]=convertirAInt(ipv4[i]);
        }
        //ahora tendremos que ordenarlo con un merge sort. en general sera O(n log (n)) por lo que la complejidad total sera O(nk+nlog(n))
        copia=mergeSortIP(copia);
        
        //ordenado en forma decreciente solo queda pasarlo al formato original copiando elemento a elemento en ipv4.
        IPv4Address[]res=new IPv4Address[copia.length];

        for(int i=0;i<copia.length;i++){
            res[i]=convertirAIPv4(copia[i]);
        }
        

        return res;
    }

    

    Router[] mergeSort(Router[]aOrdenar){
        if(aOrdenar.length<2){
            return aOrdenar;
        }else{
            Router[]lower=dividirArreglo(aOrdenar,"lower");
            Router[]higher=dividirArreglo(aOrdenar, "higher");
            
            lower=mergeSort(lower);
            higher=mergeSort(higher);
            Router[] res=fusion(lower,higher);
            return res;
        }
    }
   
    Router[] dividirArreglo(Router[]aDividir,String parte ){
    int largo=aDividir.length;
    Router[]res;
    if(largo %2!=0 && parte=="higher"){
        res=new Router[largo/2 + 1];
    }else{
        res=new Router[largo/2];
    }
    if(parte=="lower"){
        for(int i =0; i<largo/2;i++){
            res[i]=aDividir[i];
        }
    }else{
        int i=0;
        for(int j=largo/2 ;j< largo;j++){
            res[i]=aDividir[j];
            i++;
        }
    }
    return res;
    }
    
    Router[]eliminarPrimerElemento(Router[]lista){
        if(lista.length<=1){
            return new Router[0];
        }else{
            Router[] res=new Router[lista.length-1];
            System.arraycopy(lista, 1, res, 0, res.length);
            return res;
        }
    }
    
    Router[] fusion(Router[]lower,Router[]higher){

        Router[]res=new Router[lower.length+higher.length];
        int i = 0;
        while(lower.length > 0 && higher.length>0){
            
            if(lower[0].compareTo(higher[0])>=0){
                res[i]=lower[0];
                lower=eliminarPrimerElemento(lower);
                i++;
            }else{
                res[i]=higher[0];
                higher=eliminarPrimerElemento(higher);
                i++;
            }
        }

        if(lower.length>0){
            for(int j =0;j<lower.length;j++){
                res[i]=lower[j];
                i++;
            }
        }else{
            for(int j =0;j<higher.length;j++){
                res[i]=higher[j];
                i++;
            }
        }
        return res;
    }
    
    int[] convertirAInt(String ip){
        StringBuilder primerOcteto=new StringBuilder();
        StringBuilder segundoOcteto=new StringBuilder();
        StringBuilder tercerOcteto=new StringBuilder();
        StringBuilder cuartoOcteto=new StringBuilder();
        int punto=0;

        for(int i=0;i<ip.length();i++){//Aca obtengo strings de los cuartetos, discriminando los puntos.
           if (ip.charAt(i)!='.'){
                if(punto==0){//estoy en el primer octeto.
                    primerOcteto.append(ip.charAt(i));
                }else if(punto==1){//segundo octeto
                    segundoOcteto.append(ip.charAt(i));
                }else if(punto==2){
                    tercerOcteto.append(ip.charAt(i));
                }else{
                    cuartoOcteto.append(ip.charAt(i));
                }
           }else{
                punto++;
           }
        }
        //Ahora agrego los octetos a mi output.
        int[]res={Integer.parseInt(primerOcteto.toString()),
                  Integer.parseInt(segundoOcteto.toString()),
                  Integer.parseInt(tercerOcteto.toString()),
                  Integer.parseInt(cuartoOcteto.toString())
                };
        
        return res;
    }

    int[][] mergeSortIP(int[][]ipv4){

        if(ipv4.length<2){
            return ipv4;
        }else{
            int[][]lower=dividirArregloIP(ipv4,"lower");
            int[][]higher=dividirArregloIP(ipv4,"higher");

            lower=mergeSortIP(lower);
            higher=mergeSortIP(higher);
            int[][]res=fusionIP(lower,higher);
            
            return res;
        }
    }

    int[][]dividirArregloIP(int[][]aDividir,String parte){
        int largo=aDividir.length;
        int[][]res;
        if(largo%2!=0 && parte == "higher"){
            res=new int[largo/2+1][4];
        }else{
            res=new int[largo/2][4];
        }

        if(parte=="lower"){
            for(int i=0;i<largo/2;i++){
                res[i]=aDividir[i];
            }
        }else{
            int i=0;
            for(int j=largo/2;j<largo;j++){
                res[i]=aDividir[j];
                i++;
            }
        }
        return res;

    }


    int[][]fusionIP(int[][]lower,int[][]higher){
        int[][]res=new int[lower.length+higher.length][4];
        int i=0;
        int j=0;
        int k=0;

        while(i<lower.length && j<higher.length){
            // if(lower[i][0]<higher[j][0]){
            //     res[k]=higher[j];
            //     j++;
            // }else if(lower[i][0]>higher[j][0]){
            //     res[k]=lower[i];
            //     i++;
            // }else if(lower[i][1]<higher[j][1]){
            //     res[k]=higher[j];
            //     j++;
            // }else if(lower[i][1]>higher[j][1]){
            //     res[k]=lower[i];
            //     i++;
            // }else if(lower[i][2]<higher[j][2]){
            //     res[k]=higher[j];
            //     j++;
            // }else if(lower[i][2]>higher[j][2]){
            //     res[k]=lower[i];
            //     i++;
            // }else if(lower[i][3]<higher[j][3]){
            //     res[k]=higher[j];
            //     j++;
            // }else if(lower[i][3]>higher[j][3]){
            //     res[k]=lower[i];
            //     i++;
            // }else{//son todos iguales
            //     res[k]=lower[i];
            //     i++;
            // }
            int comparo=0;
            for(int columna=0;columna<4 && comparo==0;columna++){
                comparo=lower[i][columna]-higher[j][columna];
            }
            if(comparo<0){//aca lower es mas alto
                res[k]=lower[i];
                i++;
            }else if(comparo>0){
                res[k]=higher[j];
                j++;
            }else{
                res[k]=lower[i];
                i++;
            }
            k++;
        }
        //Queda copiar los elementos restantes donde los haya.
        while(i<lower.length){
            res[k]=lower[i];
            i++;
            k++;
        }
        while(j<higher.length){
            res[k]=higher[j];
            j++;
            k++;
        }
        return res;
    }

   IPv4Address convertirAIPv4(int[]aConvertir){
    return new IPv4Address(aConvertir);
   }
}