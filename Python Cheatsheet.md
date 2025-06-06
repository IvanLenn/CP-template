## Data structure

- list
  - `a.sort()` sorts a list

- deque

```python
q = collections.deque()
q.append(x)   	# Append x to the tail
q.appendleft(x) # Append x to the head
q.pop(x)
q.popleft()
```

- Stack
  - Can use a deque instead

```python
st = []
st.append()
st.pop()
```

- set

```python
st = set()
st.add(1)
st.discard(2) # st.remove(2) will error if not 2 in st
1 in st
```



- Slicing

```python
a[:] 							# Full shallow copy (outer list is new, nested objects remain shared)
a[start:stop]  		# Half-open interval
a[::-2] 				  # Reverse direction, step of 2
```

- Tuple vs. List
  - List is: mutable, uses [], not hashable, larger memory...
  - Tuple: when the content is constant / a hashable key

- defaultdict

```python
dt = collections.defaultdict(list) # dict mapping from hashable types -> list
```





## MISC

- String
  - Int to string: `str(i)`
  - Append to string: `s += 'random'`
  - ord('a') = 97, chr(97) = 'a'
  - `sorted(s)` returns a list of singleton strings
  - `str.split(",")` will split by '.'. `str.split(r"[:,.]")` will split by everything inside
- Function capture
  - read-only use -> captures the value from the nearest enclosing scope
  - Any assignment -> local binding
  - Override with nonlocal to rebind the variable from the nearest enclosing

Bitwise operator: `&, |, ^, ~, <<, >>`

Logical operator: `and, or, not`

Use `math.inf` as equvalent of `IntMax` in C++

