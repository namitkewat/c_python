while learning buffer protocol from jake's blog [post](
https://jakevdp.github.io/blog/2014/05/05/introduction-to-the-python-buffer-protocol/)

Here i have modified it according to the Chapter 15.3 from the Book "Python Cookbook, 3rd Edition by David Beazley and Brian K Jones"

Also i found [this](https://mail.python.org/pipermail/python-dev/2000-October/009974.html) mailing list response given by Guido as very useful;
### Use:

```bash
$ gcc -shared -fPIC chi2.c -o libchi2.so
$ python setup.py build_ext --inplace
$ python
Python 3.5.1 |Continuum Analytics, Inc.| (default, Dec  7 2015, 11:16:01)
[GCC 4.4.7 20120313 (Red Hat 4.4.7-1)] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import _chi
>>> import array
>>> x = array.array("d", [-1.0, 4.2, 30.6])
>>> y = array.array("d", [-1.5, 8.0, 63.0])
>>> y_error = array.array("d", [1.0, 1.5, 0.6])
>>> np_x = np.asarray(x)
>>> np_y = np.asarray(y)
>>> np_y_error = np.asarray(y_error)
>>> _chi.chi2(2.0, 1.0, x, y, y_error)
2.8988888888888766
>>> _chi.chi2(2.0, 1.0, np_x, np_y, np_y_error)
2.8988888888888766
>>> np_x[0] = -1.8
>>> _chi.chi2(2.0, 1.0, x, y, y_error)
3.858888888888877
>>> _chi.chi2(2.0, 1.0, np_x, np_y, np_y_error)
3.858888888888877
```

### Reference: <br/>
http://dan.iel.fm/posts/python-c-extensions/ <br/>
https://gist.github.com/dfm/3247796
