%raw
"const values = obj => Object.values(obj)";

[@val] external keys: 'a => Js.Array.t(string) = "values";

let jsObject = [%obj {art: "test", gueltig: true, id: 284}];

Js.log(jsObject##gueltig);

%raw
{js|const wolf = { name: "gang", getData: (title, age, szn) =>
  `${title} wolf\${wolf.name}
Alter: \${age}
Sozialversicherungsnr.: ${szn}`};|js};

type wolf;

[@bs.val] external testObjekt: wolf = "wolf";

[@bs.send]
external getDataFromTestObject:
  (
    wolf,
    ~title:  string,
    ~age:  int,
    ~szn:  string
  ) =>
  string =
  "getData";

let nameOfTestObjekt =
  testObjekt
  |> getDataFromTestObject(
       ~age= 54,
       ~szn= "444",
       ~title= "Herr",
     );

Js.log2("nameOfTestObjekt:",nameOfTestObjekt);
