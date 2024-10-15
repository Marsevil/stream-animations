import { Rect, Txt, Grid, makeScene2D } from "@motion-canvas/2d";
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
  const grid = createRef<Grid>();
  const rect = createRef<Rect>();
  const spaceship = createRef<Rect>();

  view.add(
    <>
      <Txt ref={txt} minHeight={100} fontSize={100} fill={"white"}></Txt>
      <Grid
        ref={grid}
        x={-650}
        y={255}
        width={550}
        height={550}
        stroke={"#666"}
        start={1}
        end={1}
      >
        <Rect
          ref={rect}
          x={-100}
          y={100}
          width={0}
          height={0}
          stroke={"#fff"}
          lineWidth={5}
          zIndex={1}
        ></Rect>
      </Grid>
      <Rect
        ref={spaceship}
        x={-1200}
        y={-400}
        fill={"#fff"}
        width={100}
        height={100}
      ></Rect>
    </>,
  );

  const textAppearsAnimation = function* (text: string) {
    yield* txt().text(text, 2);
  };

  const textDisappearsAnimation = function* () {
    yield* txt().text(DEFAULT, 2);
  };

  const gridAnimation = function* () {
    yield* grid().end(0, 1);
    yield* all(rect().width(150, 0.5), rect().height(100, 0.5));
    yield* waitFor(0.5);
    yield* all(rect().width(200, 0.5), rect().height(200, 0.5));
    yield* waitFor(2);
    yield* all(rect().width(0, 1), rect().height(0, 1), grid().end(1, 1));
  };

  const spaceshipAnimation = function* () {
    yield* spaceship().x(1200, 5, undefined, undefined);
  };

  yield* textAppearsAnimation(TEXT_FR);
  yield* waitFor(1);
  yield* gridAnimation();
  yield* waitFor(1);
  yield* textDisappearsAnimation();
  yield* textAppearsAnimation(TEXT_EN);
  yield* spaceshipAnimation();
  yield* waitFor(1);
  yield* textDisappearsAnimation();
});
