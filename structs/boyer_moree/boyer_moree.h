#include <iostream>
#include <algorithm>

using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;

public:
    CircularArray(int _capacity = 10);
    virtual ~CircularArray()
    {
        delete[] array;
    }

    void push_front(T data)
    {
        if (is_full())
        {
            resize();
        }

        if (back == -1)
            back = 0;
        front = prev(front);

        array[front] = data;
    }

    void push_back(T data)
    {
        if (is_full())
        {
            resize();
        }

        if (front == -1)
            front = 0;
        back = next(back);
        array[back] = data;
    }

    void insert(T data, int pos)
    {
        if (is_full())
        {
            resize();
        }

        T *temp = new T[capacity];

        for (int i = 0; i < size(); i++)
        {
            if (i == pos)
                temp[i] = data;
            else if (i < pos)
            {
                temp[i] = array[(front + i) % capacity];
            }
            else
            {
                temp[i] = array[(front + i - 1) % capacity];
            }
        }

        delete[] array;

        array = temp;
        front = 0;
        back = size() - 1;
    }

    bool find(T data)
    {
        int ind = front;

        for (int i = 0; i < size(); i++)
        {
            if (array[ind] == data)
                return true;
            ind = next(ind);
        }
        return false;
    }

    T pop_front()
    {
        if (is_empty())
            throw "error";

        T temp = array[front];
        front = next(front);
        return temp;
    }

    T pop_back()
    {
        if (is_empty())
            throw "error";
        T temp = array[back];
        back = prev(back);
        return temp;
    }

    bool is_full()
    {
        if (size() == capacity)
            return true;
        return false;
    }

    bool is_empty()
    {
        if (back == front && front == -1)
            return true;
        return false;
    }

    int size()
    {
        if (back == front && front == -1)
            return 0;
        else if (front > back)
            return (back + 1) + (capacity - front);
        else
            return back - front + 1;
    }

    void clear()
    {
        front = back = -1;
    }

    T &operator[](int val)
    {
        return array[(front + val) % capacity];
    }

    string to_string(string sep = " ")
    {
        string temp = "";
        int index = front;
        for (int i = 0; i < size(); i++)
        {
            temp += std::to_string(array[index]) + sep;
            index = next(index);
        }
        return temp;
    }

private:
    void resize()
    {
        T *temp = new T[capacity + 1];
        int index_temp = front;
        for (int i = 0; i < size(); i++)
        {
            temp[i] = array[index_temp];
            index_temp = next(index_temp);
        }
        capacity++;

        back = size() - 1;

        delete[] array;

        array = temp;
    }

    int next(int val)
    {
        val = (val + 1) % capacity;
        return val;
    }

    int prev(int val)
    {
        val = (val == 0) ? capacity - 1 : val - 1;
        return val;
    }
};

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->array = new T[_capacity];
    this->front = this->back = -1;
}

void CoincidenciaSufijoCompleto(int Cambio_array[], int arrayBorde[], string patron)
{
    int tamPatron = patron.size();
    int i = tamPatron;
    int j = tamPatron + 1;
    arrayBorde[i] = j;

    while (i > 0)
    {
        while (j <= tamPatron && patron[i - 1] != patron[j - 1])
        {
            if (Cambio_array[j] == 0)
                Cambio_array[j] = j - i;
            j = arrayBorde[j];
        }
        i--;
        j--;
        arrayBorde[i] = j;
    }
}

void CoincidenciaSufijoParcial(int Cambio_array[], int arrayBorde[], string patron)
{
    int tamPatron = patron.size();
    int j;
    j = arrayBorde[0];

    for (int i = 0; i < tamPatron; i++)
    {
        if (Cambio_array[i] == 0)
            Cambio_array[i] = j;
        if (i == j)
            j = arrayBorde[j];
    }
}

void BuscarPatron(string cadenaPrincipal, string patron, CircularArray<int> &array, int *index)
{
    int tamPatron = patron.size();
    int tamCadena = cadenaPrincipal.size();
    int arrayBorde[tamPatron + 1];
    int Cambio_array[tamPatron + 1];

    for (int i = 0; i <= tamPatron; i++)
    {
        Cambio_array[i] = 0;
    }

    CoincidenciaSufijoCompleto(Cambio_array, arrayBorde, patron);
    CoincidenciaSufijoParcial(Cambio_array, arrayBorde, patron);

    int Cambio = 0;
    int punto =0;
    int contador=-1;
//el array debe evaluar el punto donde pasa y tomarlo como un indice
    while (Cambio <= (tamCadena - tamPatron)){
        int j = tamPatron - 1;
        
        for (int i = 0; i < tamPatron; i++){
            if (cadenaPrincipal[Cambio + i] == '.'){
                contador++;
            }
        }
        //verificar si el patron y la cadena principal son iguales
        while (j >= 0 && patron[j] == cadenaPrincipal[Cambio + j] || cadenaPrincipal[Cambio + j-1] == '.'){j--;punto=contador;}
        if (j < 0){
            (*index)++;
            if(array.find(punto)==false){
                array.push_back(punto);
            }
            Cambio += Cambio_array[0];
        }
        else{
            Cambio += Cambio_array[j + 1];
        }
    }

}

/*
int main(){
                            //0    1   2    3   4    
    string cadenaPrincipal = ".Hola.Ana.Hola.Ana.Anana";
    string patron = "na";
    CircularArray<int> array;
    int index = -2;

    BuscarPatron(cadenaPrincipal, patron, array, &index);

    if (index == -1)
    {
        cout << "No hay coincidencia de patrón en la cadena principal";
    }
    else
    {
        cout << "El patrón se encuentra en la posición: ";
        for (int i = 0; i <= index; i++)
        {
            cout << array[i] << " ";//1 3 4
        }
    }
    return 0;
}*/
