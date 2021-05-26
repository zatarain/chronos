# 1. Chronos
This project aims to be an exercise to discuss about software engineering technical topics like software development, pair programming, testing, deployment, etcetera.

## 1.1 Overview
This simple command line application aims to manage `cron` expressions to generate a table with more descriptive fields.

The aplication will get the input from a single argument in the command line and it will write the result to the standard output.

## 1.2 Tenets
The primary values for the implementation will be: simplicity, readability, maintainability, testability. It should be easy to scan the code and rather quickly understand what it’s doing.

### 1.2.1 Scope and assumptions
* A valid expression will include exactly 6 space-separated fields in following order:
  *  minute
  *  hour
  *  day of month
  *  month
  *  day of week
  *  command
* The application won't handle special time string such as `"@yearly"`
* The input will be single-byte characters
* There is no spaces in the content of a single field except on the command
* The with of the label for the field name will be exactly `14` characters (filled with spaces)
* After the field *day of week* all the remaining text is considered as a command

# 2. Desing
This section aims to briefly describe the desing of the solution, description of the data, the interactions with the user and expected behaviours.

## 2.1 Workflow
1. Check we are receiving an input on the command line as an argument
   1. Report an error in case we don't get it
2. Tokenize the input from the command line
3. For each token consider as a value of the subsequent field
   1. Check the value is not empty
   2. Classify the value using regular expressions as follow:
      - **fixed**: a single numeric value (i.e. `4`)
      - **list**: this is a comma-separated list of fixed values (i.e. `2,3,4`)
      - **range**: two fixed values joined with a dash "-" (i.e. `3-7`)
      - **each**: an star followed by a slash and a number indicating frequency (i.e. `*/5`)
      - **all**: an star wich means all possible values for that field (i.e. `*`)
   3. Expand the expression according with the classification, otherwise report an error

## 2.2 Values for the fields
The value for all time fields must be quasi-numeric values.
* **minute** can take integer values in the interval `[0,60)`
* **hour** can take integer values in the interval `[0,24)`
* **day of month** can take integer values in the interval `[1,31]`
* **month** can take integer values in the interval `[1,12]`
* **day of week** can take integer values in the interval `[1,7]`
* **command** could be any non-empty `string` representing a command for shell

Some `cron`-patterns will be allowed such as list, ranges, wildcards and frequency. In particular, frequency pattern has the restriction that the size of the full range must be divided by the frequency, for instance: `*/7` is not a valid frequency for the field minute due to `7` doesn't divide `60`.

# 3. Implementation, deployment and usage
The implementation of the project has been done on C++17 using a Docker sandbox with clang compiler and Makefiles to build it.

Docker allows us to make the deployment in an isolated clean Linux-based sandbox. Therefore you will need install it before and you will need also internet access.

## 3.1 Prerequirements
* [Docker][get-docker]
* Internet connection


## 3.2 Build, tests and deployment
In order to add some unit testing [utz][utz-library] has been used in the deployment. It's a library which stills in development by myself, but for the purpose of the excersice should be enough. The test cases implemented are in the folder `utz`.

If you build the docker image with following command, you would be able to see the test cases and coverage:

```
docker image build --progress=plain -t chronos:dev .
```

This need to be run on your command line beeing on the project directory where the Dockerfile is placed.

The command should generate a container with the application.

## 3.3 Running the container
Once you have genereated the container, you will be able to run it using following command:

```
docker run -it chronos:dev
```

That should run the container interactive and then you can use the application inside the container as follow:

```
chronos "minute-expr hour-expr dayofmont-expr month-expr dayofweek-expr command"
```

For instance for following run:
```
chronos "*/15 0 1,15 * 1-5 find -iname *.txt -print -exec grep \"hello\" {} \;"
```

You should get following output:

```
minute        0 15 30 45
hour          0
day of month  1 15
month         1 2 3 4 5 6 7 8 9 10 11 12
day of week   1 2 3 4 5
command       find -iname *.txt -print -exec grep \"hello\" {} \;
```

**Note** that you would need to escape the double quotes in case you need some of them in the command field.

# 4. Further work
* Add validation and test for the ranges of individual field values
* Add support for more patterns or special characters for the fields (i.e. `#`, `?`, ...)
* Allow multi-byte characters
* Support multi-pattern fields (i.e. a list of ranges)
* Support time strings like `@yearly`, `@daily`, ...
* Refactorizations to make the application more maintainable

[utz-library]: https://github.com/zatarain/utz
[get-docker]: https://docs.docker.com/get-docker/