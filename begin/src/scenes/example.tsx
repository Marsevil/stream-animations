import { Circle, Txt, makeScene2D } from "@motion-canvas/2d";
import { DEFAULT, createRef, all, waitFor } from "@motion-canvas/core";

const BEGIN_COLOR: string = "lightseagreen";
const END_COLOR: string = "red";
const BEGIN_POSITION: number = -960;
const END_POSITION: number = 960;

const TEXT_FR: string = "Le stream va commencer";
const TEXT_EN: string = "Stream starting soon";
const TEXTS: string[] = [TEXT_FR, TEXT_EN];

export default makeScene2D(function* (view) {
  // Create your animations here

  view.fill("black");

  const txt = createRef<Txt>();

  view.add(
    <>
      <Txt ref={txt} minHeight={100} fontSize={100} fill={"white"}></Txt>
    </>,
  );

  const txtAnimator = (function* () {
    for (const text of TEXTS) {
      yield* txt().text(text, 2);
      yield* waitFor(4);
      yield* txt().text(DEFAULT, 2);
      yield* waitFor(1);
    }
  })();

  yield* all(txtAnimator);
});
