## To find any number is 2s power there are 3 methods:

1. By using ceil and floor of `log2`

```cpp
bool isPowerOfTwo(int n)
{
    if(n == 0){
	    return false;
    }
    return (ceil(log2(n)) == floor(log2(n)));
}
```

2. Using bit manipulation:

```cpp
bool isPowerOfTwo(int n)
{
    if (n == 0)
        return 0;
    while (n != 1) {
        if (n % 2 != 0)
            return 0;
        n = n / 2;
    }
    return 1;
}
```

3. Easy and efficient method

```cpp
bool isPowerOfTwo(int n){
	return n&(n-1) == 0;
}
```

