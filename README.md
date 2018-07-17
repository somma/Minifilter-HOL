# 미니필터 드라이버 개발 실습

BoB 7th, programming lecture by somma (fixbrain@gmail.com)

---

## 개발 환경 설정

[Download the Windows Driver Kit (WDK)](https://developer.microsoft.com/en-us/windows/hardware/windows-driver-kit) 를 참조해서 개발 툴을 설치

1. Visual Studio 설치 

    + Visual studio 2017 설치
    + 반드시 C/C++ 개발환경을 모두 설치 (설치 옵션 선택)

1. WDK 설치

1. Virtual KD 설치 ( [Virtual KD](http://virtualkd.sysprogs.org/) )

    + [install](http://virtualkd.sysprogs.org/tutorials/install/) 에 설명된 대로 Debugger/Debuggee 설정을 완료할 것
    + Debuggee 의 커널을 Break 할 수 있는지 반드시 확인할 것

1. git 설치 

    + [git for Windows](https://git-for-windows.github.io/)
    + [tortoise git](https://tortoisegit.org/download/)

1. vcpkg 설치 I (직접 빌드하기))
    
    자세한 내용은 https://github.com/Microsoft/vcpkg 의 README.md 를 참고

    1. 소스코드 가져오기

            C:\>git clone https://github.com/Microsoft/vcpkg.git c:\work.vcpkg
            Cloning into 'c:\work.vcpkg'...
            ...

    1. 빌드

            C:\work.vcpkg>c:\work.vcpkg\bootstrap-vcpkg.bat
            Microsoft (R) Build Engine version 14.0.25420.1
            ...

    1. 패키지 설치
            
            vcpkg   install boost:x86-windows boost:x86-windows-static boost:x64-windows boost:x64-windows-static \
                    curl:x86-windows curl:x86-windows-static curl:x64-windows curl:x64-windows-static \
                    sqlite3:x86-windows sqlite3:x86-windows-static sqlite3:x64-windows sqlite3:x64-windows-static \
                    jsoncpp:x86-windows jsoncpp:x86-windows-static jsoncpp:x64-windows jsoncpp:x64-windows-static \
                    gtest:x86-windows gtest:x86-windows-static gtest:x64-windows gtest:x64-windows-static

    1. Visual Studio 연동 

            C:\work.vcpkg>vcpkg integrate install
            Applied user-wide integration for this vcpkg root.

            All MSBuild C++ projects can now #include any installed libraries.
            Linking will be handled automatically.
            Installing new libraries will make them instantly available.

            CMake projects should use -DCMAKE_TOOLCHAIN_FILE=C:/work.vcpkg/scripts/buildsystems/vcpkg.cmake


1. vcpkg 설치 II (빌드된 바이너리 사용하기 )

    vcpkg 빌드에 문제가 있는 경우 visual studio 2017 용으로 미리 빌드된 바이너리를 다운로드 할 수 있습니다. 

    1. 미리 빌드된 바이너리를 [여기](https://drive.google.com/open?id=1ieMxcymfsfd-H8XK74j9nQxv84E4l31W)에서 다운로드합니다. 
    1. vcpkg 폴더에 덮어씁니다 (!끝!)
    1. Visual Studio 연동 

            C:\work.vcpkg>vcpkg integrate install
            Applied user-wide integration for this vcpkg root.

            All MSBuild C++ projects can now #include any installed libraries.
            Linking will be handled automatically.
            Installing new libraries will make them instantly available.

            CMake projects should use -DCMAKE_TOOLCHAIN_FILE=C:/work.vcpkg/scripts/buildsystems/vcpkg.cmake

            C:\work.vcpkg>


1. `_MyLib` 가져오기 

    Windows programming 에 도움되는 유틸리티 모듈입니다. 

    1. `_MyLib` 소스코드 클로닝

            C:\>git clone https://github.com/somma/_MyLib.git c:\work.mylib
            Cloning into 'c:\work.mylib'...
            ...

    1. `_MyLib` 소스코드 빌드 
        _MyLib 을 빌드가 완료되면 `x:\` 드라이브에 생성된 실행파일을 복사하도록 설정되어있으므로 _MyLib 의 속성페이지에 들어가서 아래 Post-BuildEvent 섹션에 정의된 내용을 삭제한다. 

        ![img](.\image_00\img00.png)


1. WDK 샘플 빌드

    + 개발환경에 [Windows-driver-samples](https://github.com/Microsoft/Windows-driver-samples) 을 다운로드 혹은 clone 해 둔다. 
    + `Windows-driver-samples/filesys/miniFilter/` 아래에 있는 프로젝트들을 Visual studio 2017 를 통해 빌드해본다. 
    + 깔끔하게 빌드가 되지 않는다면 뭔가 문제가 있는것이니 자신의 환경설정에 문제가 없는지 다시 한번 확인한다.


## 커널 디버깅 환경 설정 

+ VMWARE (Virtual Box 도 가능)
+ Windows 10 x64 가상머신 
    + 직접 설치해서 가져오길 권장
    + 아니면 [Free Windows Image](https://developer.microsoft.com/en-us/microsoft-edge/tools/vms/) 에서 다운로드
+ [Virtual KD](http://virtualkd.sysprogs.org/)
    + [install](http://virtualkd.sysprogs.org/tutorials/install/) 에 설명된 대로 Debugger/Debuggee 설정을 완료할 것        


## 기타 

+ macbook 사용자입니다. 어떻게 하죠?

    인터넷 찾아보면 두개의 windows 가상머신을 통해서 커널디버깅 가능한 시나리오가 많이 있습니다. 인터넷에서 찾아보고, 설정해오세요.

+ linux 사용자는요?

    마찬가지. virtual box 로 windows 인스턴스 두개 띄워서 가상머신 끼리 커널디버깅 가능합니다. 인터넷에서 찾아보고, 설정해오세요.

+ 전 visual studio 2015 를 설치했는데요?

    visual studio 2017 을 설치하세요.

+ 잘 안되는데요?

    될때까지 해보세요. 구글링도 좀 해보구요.    