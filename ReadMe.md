﻿## Projcet : 코드 리뷰 툴

### 목표 기능
[개요]
* 코드 리뷰시에 리뷰 문서를 작성하고, 리뷰 내용과 코드 내용이 분리되어 한 번에 보기가 비교적 불편하였습니다.
  이에 작성한 코드리뷰 문서와 코드를 함께 볼 수 있도록 하여 편리성을 목표로 제작하였습니다.

[상세]

1. 리뷰 문서 파일을 불러 옴.
2. 문서 파일을 파싱하고 그에 맞추어서 revision과 파일명, 소스코드 등을 보여 줌.
3. 이동 버튼을 누르면 해당 라인에 맞춰서 코드 스크롤 됨.

### 실행 테스트(160323)
* 프로젝트 폴더 내의 temporaryCodeDir 폴더에 테스트용 리뷰파일을 올렸습니다.
* 그 파일의 형식대로 작성하고 프로그램을 통해 파일을 읽으면 동작합니다.
* url의 경우 로컬 url이기 때문에 자신의 svn repository url을 작성해줘야 합니다.
* 또한 tortoise svn의 "command line client tools" 추가 설치 해야합니다.
* 현재 ANSI 인코딩만 지원합니다.

### 변경 전 프로젝트
### 목표 기능
__[개요]

* 코드 리뷰시에 코드에 대해 코멘트를 달 때 코드와 분리하여 코멘트를 썼던, 그리고 코멘트를 볼 때도 코드와 분리하여 봐야 하는 불편함이 있었습니다.
  이에 코드에 바로 코멘트를 달고, 저장 시 코멘트만을 따로 저장하고 공유하여 코드리뷰를 좀 더 편하게 하고자 했습니다.

__[상세]

1. SVN에 외부 툴로 등록하여 실행 시 코드를 불러 옴.
2. 창을 두 개로 분할하여 변경 전 코드와 변경 후 코드를 함께 보여줌
3. 왼쪽, 오른쪽 창 중 오른쪽 창에서는 코드에 코멘트를 달 수 있음.

4. 저장을 하게 되면, 코멘트(1)와 코멘트를 단 라인(2)을 파일로 저장.
5. 파일은 SVN의 특정 repository에 저장.

6. 저장한 파일을 불러오기 하면 헤더를 확인하여 어떤 파일인지 확인 후 행동 결정.
   1) 코멘트를 새로 달 것인지.
   2) 달려있는 코멘트를 볼 것인지.
7. 1)인 경우 목표 기능의 1번으로 돌아감.
   2)인 경우 관련한 source코드와 함께 코멘트를 보여줌.

### 실행 테스트
* 현재 svn과 연동하지 않아 argument에 테스트용 코드파일명을 정적으로 넣어주고 있습니다.
* 디버그 모드로만 진행했으며 릴리즈 모드는 진행하지 않았습니다.